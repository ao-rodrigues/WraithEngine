//
// Renderer.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include "Wraith/Singleton.h"

#include "Graphics/Vulkan.h"

#include "Graphics/Device.h"
#include "Graphics/Swapchain.h"
#include "Graphics/Renderable.h"

#include "Platform/Window.h"

namespace Wraith {

    class Renderer : public Singleton<Renderer> {
    public:
        struct GPUCameraData {
            glm::mat4 view;
            glm::mat4 proj;
            glm::mat4 viewProj;
        };
        struct FrameData {
            VkSemaphore renderSemaphore = VK_NULL_HANDLE;
            VkSemaphore presentSemaphore = VK_NULL_HANDLE;
            VkFence renderFence = VK_NULL_HANDLE;

            VkCommandPool commandPool = VK_NULL_HANDLE;
            VkCommandBuffer commandBuffer = VK_NULL_HANDLE;

            AllocatedBuffer cameraBuffer;

            VkDescriptorSet globalDescriptor = VK_NULL_HANDLE;
        };

        void Init(const Device& device, Window& window);

        void RenderFrame(std::function<void(VkCommandBuffer)>&& drawRenderables);

        VkRenderPass GetRenderPass() const { return _renderPass; }
        VkDescriptorSetLayout GetGlobalDescriptorSetLayout() const { return _globalSetLayout; }
        FrameData& GetCurrentFrame();

    private:
        void RecreateSwapchain();
        void CreateCommandBuffers();
        void CreateRenderPass();
        void CreateFramebuffers();
        void CreateSyncStructures();
        void CreateDescriptors();


        VkCommandBuffer BeginFrame();
        void BeginRenderPass(VkCommandBuffer commandBuffer);
        void EndRenderPass(VkCommandBuffer commandBuffer);
        void EndFrame();
        void SubmitCommandQueue();

        static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

        Device::Ref _device;
        Window::MutableRef _window;

        Swapchain _swapchain;

        std::vector<VkFramebuffer> _framebuffers;
        VkRenderPass _renderPass = VK_NULL_HANDLE;
        std::array<FrameData, MAX_FRAMES_IN_FLIGHT> _frames;

        uint32_t _swapChainImageIndex = 0;
        size_t _frameIndex = 0;

        VkDescriptorSetLayout _globalSetLayout = VK_NULL_HANDLE;
        VkDescriptorPool _descriptorPool = VK_NULL_HANDLE;
    };
}
