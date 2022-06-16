#include "wrpch.h"
#include "Renderer.h"

#include "Platform/Window.h"

#include "Graphics/SwapChain.h"
#include "Graphics/Device.h"

namespace Wraith {
    Renderer::Renderer(Device& device, Window& window)
            : _device(device), _window(window) {
        RecreateSwapChain();
        CreateCommandBuffers();
    }

    Renderer::~Renderer() {
        FreeCommandBuffers();
    }

    VkCommandBuffer Renderer::BeginFrame() {
        WR_ASSERT(!_frameStarted, "Can't call BeginFrame while frame is in progress!")

        const VkResult result = _swapChain->AcquireNextImage(&_currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            RecreateSwapChain();
            return nullptr;
        }
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to acquire swap chain image!");
        }

        _frameStarted = true;

        const VkCommandBuffer commandBuffer = GetCurrentCommandBuffer();
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("Failed to begin recording command buffer!");
        }

        return commandBuffer;
    }

    void Renderer::BeginSwapChainRenderPass(VkCommandBuffer commandBuffer) {
        WR_ASSERT(_frameStarted, "Can't call BeginSwapChainRenderPass if frame is not in progress!")
        WR_ASSERT(commandBuffer == GetCurrentCommandBuffer(),
                  "Can't begin render pass on a command buffer from a different frame!")

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = _swapChain->GetRenderPass();
        renderPassInfo.framebuffer = _swapChain->GetFramebuffer(_currentImageIndex);
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = _swapChain->GetExtent();

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
        viewport.width = static_cast<float>(_swapChain->GetExtent().width);
        viewport.height = static_cast<float>(_swapChain->GetExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        const VkRect2D scissor{{0, 0}, _swapChain->GetExtent()};

        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    }

    void Renderer::EndSwapChainRenderPass(VkCommandBuffer commandBuffer) {
        WR_ASSERT(_frameStarted, "Can't call EndSwapChainRenderPass if frame is not in progress!")
        WR_ASSERT(commandBuffer == GetCurrentCommandBuffer(),
                  "Can't end render pass on a command buffer from a different frame!")

        vkCmdEndRenderPass(commandBuffer);
    }

    void Renderer::EndFrame() {
        WR_ASSERT(_frameStarted, "Can't call EndFrame while frame is not in progress!")

        const VkCommandBuffer commandBuffer = GetCurrentCommandBuffer();
        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("Failed to record command buffer!");
        }

        const VkResult result = _swapChain->SubmitCommandBuffers(&commandBuffer, &_currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _window.WasResized()) {
            _window.ResetWindowResizedFlag();
            RecreateSwapChain();
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to present swap chain image!");
        }

        _frameStarted = false;
        _currentFrameIndex = (_currentFrameIndex + 1) % SwapChain::MAX_FRAMES_IN_FLIGHT;
    }

    VkCommandBuffer Renderer::GetCurrentCommandBuffer() const {
        WR_ASSERT(_frameStarted, "Cannot get command buffer when frame is not in progress!")
        return _commandBuffers[_currentFrameIndex];
    }

    void Renderer::CreateCommandBuffers() {
        _commandBuffers.resize(SwapChain::MAX_FRAMES_IN_FLIGHT);

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = _device.GetCommandPool();
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = static_cast<uint32_t>(SwapChain::MAX_FRAMES_IN_FLIGHT);

        if (vkAllocateCommandBuffers(_device.GetDevice(), &allocInfo, _commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffers!");
        }
        WR_LOG_DEBUG("Allocated command buffers.")
    }

    void Renderer::FreeCommandBuffers() {
        vkFreeCommandBuffers(_device.GetDevice(), _device.GetCommandPool(),
                             static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());
    }

    void Renderer::RecreateSwapChain() {
        auto extent = _window.GetExtent();
        while (extent.width == 0 || extent.height == 0) {
            extent = _window.GetExtent();
            _window.WaitEvents();
        }

        if (_swapChain != nullptr) {
            _device.FinishOperations();
            _swapChain.reset();
        }
        _swapChain = std::make_unique<SwapChain>(_device, _window);
    }
}
