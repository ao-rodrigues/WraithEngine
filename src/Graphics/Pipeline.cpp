#include "wrpch.h"
#include "Pipeline.h"

#include "Device.h"

namespace Wraith {
    Pipeline::Pipeline(Device& device, VkPipeline pipeline, VkPipelineLayout pipelineLayout)
        : _device(device), _pipeline(pipeline), _pipelineLayout(pipelineLayout) {}

    Pipeline::~Pipeline() {
        vkDestroyPipeline(_device.GetDevice(), _pipeline, nullptr);
        vkDestroyPipelineLayout(_device.GetDevice(), _pipelineLayout, nullptr);
    }

    void Pipeline::Bind(VkCommandBuffer commandBuffer) const {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline);
    }
}
