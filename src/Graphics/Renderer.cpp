//
// Renderer.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"
#include "Renderer.h"

#include "Core/Assert.h"
#include "Core/Engine.h"
#include "Platform/Window.h"
#include "Graphics/Device.h"
#include "Graphics/VkFactory.h"

namespace Wraith {
    void Renderer::Init(const Device& device, Window& window) {
        _device = device;
        _window = window;

        RecreateSwapchain();
        CreateCommandBuffers();
        CreateRenderPass();
        CreateFramebuffers();
        CreateSyncStructures();
        CreateDescriptors();
    }

    void Renderer::RenderFrame(std::function<void(VkCommandBuffer)>&& drawRenderables) {
        if (VkCommandBuffer commandBuffer = BeginFrame()) {
            BeginRenderPass(commandBuffer);

            // TODO use ECS to get all entities with Renderable components
            drawRenderables(commandBuffer);

            EndRenderPass(commandBuffer);
            EndFrame();
        }
    }

    void Renderer::RecreateSwapchain() {
        auto extent = _window->GetExtent();
        while (extent.width == 0 || extent.height == 0) {
            extent = _window->GetExtent();
            _window->WaitEvents();
        }

        if (!_swapchain.IsUndefined()) {
            _device->FinishOperations();
            _swapchain.Destroy();
        }
        _swapchain.Create(_device, _window);
    }

    void Renderer::CreateCommandBuffers() {
        for (auto& frame : _frames) {
            frame.commandPool = _device->CreateCommandPool();

            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.commandPool = frame.commandPool;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandBufferCount = 1;

            WR_VK_CHECK_MSG(vkAllocateCommandBuffers(_device->GetVkDevice(), &allocInfo, &frame.commandBuffer), "Failed to allocate command buffer!")

            Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
                vkDestroyCommandPool(_device->GetVkDevice(), frame.commandPool, nullptr);
            });
        }
        WR_LOG_DEBUG("Created command buffers!")
    }

    void Renderer::CreateRenderPass() {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = _swapchain.GetImageFormat();
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentDescription depthAttachment{};
        depthAttachment.format = _swapchain.GetDepthImageFormat();
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depthAttachmentRef{};
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;

        VkAttachmentDescription attachments[2] = {colorAttachment, depthAttachment};

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 2;
        renderPassInfo.pAttachments = &attachments[0];
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkSubpassDependency depthDependency{};
        depthDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        depthDependency.dstSubpass = 0;
        depthDependency.srcStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        depthDependency.srcAccessMask = 0;
        depthDependency.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        depthDependency.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        VkSubpassDependency dependencies[2] = {dependency, depthDependency};

        renderPassInfo.dependencyCount = 2;
        renderPassInfo.pDependencies = &dependencies[0];

        WR_VK_CHECK_MSG(vkCreateRenderPass(_device->GetVkDevice(), &renderPassInfo, nullptr, &_renderPass), "Failed to create render pass!")
        WR_LOG_DEBUG("Created render pass!")

        Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
            vkDestroyRenderPass(_device->GetVkDevice(), _renderPass, nullptr);
        });
    }

    void Renderer::CreateFramebuffers() {
        const auto& imageViews = _swapchain.GetImageViews();
        auto swapChainExtent = _swapchain.GetExtent();

        _framebuffers.resize(imageViews.size());
        for (size_t i = 0; i < imageViews.size(); i++) {
            VkImageView attachments[2] = {
                    imageViews[i],
                    _swapchain.GetDepthImageView()
            };

            VkFramebufferCreateInfo framebufferInfo = VkFactory::FramebufferCreateInfo(_renderPass, attachments, swapChainExtent);
            WR_VK_CHECK_MSG(vkCreateFramebuffer(_device->GetVkDevice(), &framebufferInfo, nullptr, &_framebuffers[i]), "Failed to create framebuffer!")
        }
        WR_LOG_DEBUG("Created Framebuffers!")

        Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
            _swapchain.Destroy();
            for (auto& framebuffer : _framebuffers) {
                vkDestroyFramebuffer(_device->GetVkDevice(), framebuffer, nullptr);
            }
        });
    }

    void Renderer::CreateSyncStructures() {
        VkFenceCreateInfo fenceInfo = VkFactory::FenceCreateInfo();
        VkSemaphoreCreateInfo semaphoreInfo = VkFactory::SemaphoreCreateInfo();

        for (auto& frame : _frames) {
            WR_VK_CHECK_MSG(vkCreateFence(_device->GetVkDevice(), &fenceInfo, nullptr, &frame.renderFence), "Failed to create Render fence!")

            Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
                vkDestroyFence(_device->GetVkDevice(), frame.renderFence, nullptr);
            });

            WR_VK_CHECK_MSG(vkCreateSemaphore(_device->GetVkDevice(), &semaphoreInfo, nullptr, &frame.renderSemaphore), "Failed to create Render semaphore!")
            WR_VK_CHECK_MSG(vkCreateSemaphore(_device->GetVkDevice(), &semaphoreInfo, nullptr, &frame.presentSemaphore), "Failed to create Present semaphore!")

            Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
                vkDestroySemaphore(_device->GetVkDevice(), frame.renderSemaphore, nullptr);
                vkDestroySemaphore(_device->GetVkDevice(), frame.presentSemaphore, nullptr);
            });
        }
        WR_LOG_DEBUG("Created Sync Structures!")
    }

    void Renderer::CreateDescriptors() {
        VkDescriptorSetLayoutBinding camBufferBinding{};
        camBufferBinding.binding = 0;
        camBufferBinding.descriptorCount = 1;
        camBufferBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        camBufferBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo setInfo = VkFactory::DescriptorSetLayoutCreateInfo(1, &camBufferBinding);
        WR_VK_CHECK_MSG(vkCreateDescriptorSetLayout(_device->GetVkDevice(), &setInfo, nullptr, &_globalSetLayout), "Unable to create Descriptor set layout!")

        const std::vector<VkDescriptorPoolSize> poolSizes = {
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 10 }
        };
        VkDescriptorPoolCreateInfo poolInfo = VkFactory::DescriptorPoolCreateInfo(10, poolSizes);
        WR_VK_CHECK_MSG(vkCreateDescriptorPool(_device->GetVkDevice(), &poolInfo, nullptr, &_descriptorPool), "Unable to create Descriptor pool!")

        Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
            vkDestroyDescriptorSetLayout(_device->GetVkDevice(), _globalSetLayout, nullptr);
            vkDestroyDescriptorPool(_device->GetVkDevice(), _descriptorPool, nullptr);
        });

        for (auto& frame : _frames) {
            frame.cameraBuffer = _device->CreateBuffer(sizeof(GPUCameraData), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);
            Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
                vmaDestroyBuffer(_device->GetAllocator(), frame.cameraBuffer.buffer, frame.cameraBuffer.allocation);
            });

            VkDescriptorSetAllocateInfo allocInfo{};
            allocInfo.pNext = nullptr;
            allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            allocInfo.descriptorPool = _descriptorPool;
            allocInfo.descriptorSetCount = 1;
            allocInfo.pSetLayouts = &_globalSetLayout;

            WR_VK_CHECK_MSG(vkAllocateDescriptorSets(_device->GetVkDevice(), &allocInfo, &frame.globalDescriptor), "Unable to allocate Descriptor set!")

            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = frame.cameraBuffer.buffer;
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(GPUCameraData);

            VkWriteDescriptorSet setWrite{};
            setWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            setWrite.pNext = nullptr;
            setWrite.dstBinding = 0;
            setWrite.dstSet = frame.globalDescriptor;
            setWrite.descriptorCount = 1;
            setWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            setWrite.pBufferInfo = &bufferInfo;

            vkUpdateDescriptorSets(_device->GetVkDevice(), 1, &setWrite, 0, nullptr);
        }

        WR_LOG_DEBUG("Created Descriptors!")
    }

    Renderer::FrameData& Renderer::GetCurrentFrame() {
        return _frames[_frameIndex % MAX_FRAMES_IN_FLIGHT];
    }

    VkCommandBuffer Renderer::BeginFrame() {
        FrameData& frame = GetCurrentFrame();
        WR_VK_CHECK_MSG(vkWaitForFences(_device->GetVkDevice(), 1, &frame.renderFence, true, 1000000000), "Unable to wait for Render fence!")
        WR_VK_CHECK_MSG(vkResetFences(_device->GetVkDevice(), 1, &frame.renderFence), "Unable to reset Render fence!")

        const VkResult result = _swapchain.AcquireNextImage(&_swapChainImageIndex, 1000000000, frame.presentSemaphore);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            RecreateSwapchain();
            return nullptr;
        }
        if (result != VK_SUCCESS) {
            WR_LOG_ERROR("Failed to acquire swap chain image!")
            abort();
        }

        VkCommandBuffer commandBuffer = GetCurrentFrame().commandBuffer;
        WR_VK_CHECK_MSG(vkResetCommandBuffer(commandBuffer, 0), "Unable to reset command buffer!")

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        WR_VK_CHECK_MSG(vkBeginCommandBuffer(commandBuffer, &beginInfo), "Failed to begin recording command buffer!")
        return commandBuffer;
    }

    void Renderer::BeginRenderPass(VkCommandBuffer commandBuffer) {
        WR_ASSERT_MSG(commandBuffer == GetCurrentFrame().commandBuffer, "Can't begin render pass on a command buffer from a different frame!")

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = _renderPass;
        renderPassInfo.framebuffer = _framebuffers[_swapChainImageIndex];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = _swapchain.GetExtent();

        VkClearValue clearColor;
        clearColor.color = {0.0f, 0.0f, 0.0f};

        VkClearValue depthClear;
        depthClear.depthStencil.depth = 1.0f;

        VkClearValue clearValues[2] = {clearColor, depthClear};
        renderPassInfo.clearValueCount = 2;
        renderPassInfo.pClearValues = &clearValues[0];

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(_swapchain.GetExtent().width);
        viewport.height = static_cast<float>(_swapchain.GetExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        const VkRect2D scissor{{0, 0}, _swapchain.GetExtent()};

        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    }

    void Renderer::EndRenderPass(VkCommandBuffer commandBuffer) {
        WR_ASSERT_MSG(commandBuffer == GetCurrentFrame().commandBuffer, "Can't end render pass on a command buffer from a different frame!")
        vkCmdEndRenderPass(commandBuffer);
    }

    void Renderer::EndFrame() {
        VkCommandBuffer commandBuffer = GetCurrentFrame().commandBuffer;
        WR_VK_CHECK_MSG(vkEndCommandBuffer(commandBuffer), "Failed to record command buffer!")

        SubmitCommandQueue();

        VkResult result = _swapchain.Present(GetCurrentFrame().renderSemaphore, &_swapChainImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _window->WasResized()) {
            _window->ResetWindowResizedFlag();
            RecreateSwapchain();
        } else if (result != VK_SUCCESS) {
            WR_LOG_ERROR("Failed to present swap chain image!")
            abort();
        }

        _frameIndex++;
    }

    void Renderer::SubmitCommandQueue() {
        FrameData& frame = GetCurrentFrame();

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        const VkPipelineStageFlags waitStages[] = {
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
        };
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &frame.presentSemaphore;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &frame.commandBuffer;

        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &frame.renderSemaphore;

        WR_VK_CHECK_MSG(vkQueueSubmit(_device->GetGraphicsQueue(), 1, &submitInfo, frame.renderFence), "Unable to submit command queue!")
    }
}
