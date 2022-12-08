//
// Pipeline.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include "Graphics/Device.h"
#include "Graphics/Vulkan.h"

namespace Wraith {

    class Pipeline {
    public:
        Pipeline(const Device& device, VkPipeline pipeline, VkPipelineLayout pipelineLayout);
        ~Pipeline();

        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(const Pipeline&) = delete;

        void Bind(VkCommandBuffer commandBuffer) const;

        VkPipeline GetVkPipeline() const { return _pipeline; }
        VkPipelineLayout GetPipelineLayout() const { return _pipelineLayout; }

    private:
        Device::Ref _device;

        VkPipeline _pipeline = VK_NULL_HANDLE;
        VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
    };
}
