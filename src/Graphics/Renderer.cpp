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
        m_Device = device;
        m_Window = window;

        RecreateSwapchain();
        CreateCommandBuffers();
        CreateRenderPass();
        CreateFramebuffers();
        CreateSyncStructures();
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
        auto extent = m_Window->GetExtent();
        while (extent.width == 0 || extent.height == 0) {
            extent = m_Window->GetExtent();
            m_Window->WaitEvents();
        }

        if (!m_Swapchain.IsUndefined()) {
            m_Device->FinishOperations();
            m_Swapchain.Destroy();
        }
        m_Swapchain.Create(m_Device, m_Window);
    }

    void Renderer::CreateCommandBuffers() {
        for (auto& frame : m_Frames) {
            frame.CommandPool = m_Device->CreateCommandPool();

            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.commandPool = frame.CommandPool;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandBufferCount = 1;

            WR_VK_CHECK_MSG(vkAllocateCommandBuffers(m_Device->GetVkDevice(), &allocInfo, &frame.CommandBuffer), "Failed to allocate command buffer!")

            Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
                vkDestroyCommandPool(m_Device->GetVkDevice(), frame.CommandPool, nullptr);
            });
        }
        WR_LOG_DEBUG("Created command buffers!")
    }

    void Renderer::CreateRenderPass() {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = m_Swapchain.GetImageFormat();
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
        depthAttachment.format = m_Swapchain.GetDepthImageFormat();
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

        WR_VK_CHECK_MSG(vkCreateRenderPass(m_Device->GetVkDevice(), &renderPassInfo, nullptr, &m_RenderPass), "Failed to create render pass!")
        WR_LOG_DEBUG("Created render pass!")

        Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
            vkDestroyRenderPass(m_Device->GetVkDevice(), m_RenderPass, nullptr);
        });
    }

    void Renderer::CreateFramebuffers() {
        const auto& imageViews = m_Swapchain.GetImageViews();
        auto swapChainExtent = m_Swapchain.GetExtent();

        m_Framebuffers.resize(imageViews.size());
        for (size_t i = 0; i < imageViews.size(); i++) {
            VkImageView attachments[2] = {
                    imageViews[i],
                    m_Swapchain.GetDepthImageView()
            };

            VkFramebufferCreateInfo framebufferInfo = VkFactory::FramebufferCreateInfo(m_RenderPass, attachments, swapChainExtent);
            WR_VK_CHECK_MSG(vkCreateFramebuffer(m_Device->GetVkDevice(), &framebufferInfo, nullptr, &m_Framebuffers[i]), "Failed to create framebuffer!")
        }
        WR_LOG_DEBUG("Created Framebuffers!")

        Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
            m_Swapchain.Destroy();
            for (auto& framebuffer : m_Framebuffers) {
                vkDestroyFramebuffer(m_Device->GetVkDevice(), framebuffer, nullptr);
            }
        });
    }

    void Renderer::CreateSyncStructures() {
        VkFenceCreateInfo fenceInfo = VkFactory::FenceCreateInfo();
        VkSemaphoreCreateInfo semaphoreInfo = VkFactory::SemaphoreCreateInfo();

        for (auto& frame : m_Frames) {
            WR_VK_CHECK_MSG(vkCreateFence(m_Device->GetVkDevice(), &fenceInfo, nullptr, &frame.RenderFence), "Failed to create Render fence!")

            Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
                vkDestroyFence(m_Device->GetVkDevice(), frame.RenderFence, nullptr);
            });

            WR_VK_CHECK_MSG(vkCreateSemaphore(m_Device->GetVkDevice(), &semaphoreInfo, nullptr, &frame.RenderSemaphore), "Failed to create Render semaphore!")
            WR_VK_CHECK_MSG(vkCreateSemaphore(m_Device->GetVkDevice(), &semaphoreInfo, nullptr, &frame.PresentSemaphore), "Failed to create Present semaphore!")

            Engine::GetInstance().GetMainDeletionQueue().Push([=]() {
                vkDestroySemaphore(m_Device->GetVkDevice(), frame.RenderSemaphore, nullptr);
                vkDestroySemaphore(m_Device->GetVkDevice(), frame.PresentSemaphore, nullptr);
            });
        }
        WR_LOG_DEBUG("Created Sync Structures!")
    }

    Renderer::FrameData& Renderer::GetCurrentFrame() {
        return m_Frames[m_FrameIndex % k_MaxFramesInFlight];
    }

    VkCommandBuffer Renderer::BeginFrame() {
        FrameData& frame = GetCurrentFrame();
        WR_VK_CHECK_MSG(vkWaitForFences(m_Device->GetVkDevice(), 1, &frame.RenderFence, true, 1000000000), "Unable to wait for Render fence!")
        WR_VK_CHECK_MSG(vkResetFences(m_Device->GetVkDevice(), 1, &frame.RenderFence), "Unable to reset Render fence!")

        const VkResult result = m_Swapchain.AcquireNextImage(&m_SwapChainImageIndex, 1000000000, frame.PresentSemaphore);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            RecreateSwapchain();
            return nullptr;
        }
        if (result != VK_SUCCESS) {
            WR_LOG_ERROR("Failed to acquire swap chain image!")
            abort();
        }

        VkCommandBuffer commandBuffer = GetCurrentFrame().CommandBuffer;
        WR_VK_CHECK_MSG(vkResetCommandBuffer(commandBuffer, 0), "Unable to reset command buffer!")

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        WR_VK_CHECK_MSG(vkBeginCommandBuffer(commandBuffer, &beginInfo), "Failed to begin recording command buffer!")
        return commandBuffer;
    }

    void Renderer::BeginRenderPass(VkCommandBuffer commandBuffer) {
        WR_ASSERT_MSG(commandBuffer == GetCurrentFrame().CommandBuffer, "Can't begin render pass on a command buffer from a different frame!")

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = m_RenderPass;
        renderPassInfo.framebuffer = m_Framebuffers[m_SwapChainImageIndex];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = m_Swapchain.GetExtent();

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
        viewport.width = static_cast<float>(m_Swapchain.GetExtent().width);
        viewport.height = static_cast<float>(m_Swapchain.GetExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        const VkRect2D scissor{{0, 0}, m_Swapchain.GetExtent()};

        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    }

    void Renderer::EndRenderPass(VkCommandBuffer commandBuffer) {
        WR_ASSERT_MSG(commandBuffer == GetCurrentFrame().CommandBuffer, "Can't end render pass on a command buffer from a different frame!")
        vkCmdEndRenderPass(commandBuffer);
    }

    void Renderer::EndFrame() {
        VkCommandBuffer commandBuffer = GetCurrentFrame().CommandBuffer;
        WR_VK_CHECK_MSG(vkEndCommandBuffer(commandBuffer), "Failed to record command buffer!")

        SubmitCommandQueue();

        VkResult result = m_Swapchain.Present(GetCurrentFrame().RenderSemaphore, &m_SwapChainImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_Window->WasResized()) {
            m_Window->ResetWindowResizedFlag();
            RecreateSwapchain();
        } else if (result != VK_SUCCESS) {
            WR_LOG_ERROR("Failed to present swap chain image!")
            abort();
        }

        m_FrameIndex++;
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
        submitInfo.pWaitSemaphores = &frame.PresentSemaphore;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &frame.CommandBuffer;

        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &frame.RenderSemaphore;

        WR_VK_CHECK_MSG(vkQueueSubmit(m_Device->GetGraphicsQueue(), 1, &submitInfo, frame.RenderFence), "Unable to submit command queue!")
    }
}
