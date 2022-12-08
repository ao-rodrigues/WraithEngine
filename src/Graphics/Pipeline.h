#pragma once

#include "Vulkan.h"

namespace Wraith {
    class Device;

    class Pipeline {
    public:
        Pipeline(Device& device, VkPipeline pipeline, VkPipelineLayout pipelineLayout);
        ~Pipeline();

        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(const Pipeline&) = delete;

        void Bind(VkCommandBuffer commandBuffer) const;

        VkPipeline GetVkPipeline() const { return _pipeline; }
        VkPipelineLayout GetPipelineLayout() const { return _pipelineLayout; }

    private:
        Device& _device;

        VkPipeline _pipeline = VK_NULL_HANDLE;
        VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
    };
}
