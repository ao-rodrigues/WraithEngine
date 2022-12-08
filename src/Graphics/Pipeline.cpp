﻿//
// Pipeline.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"
#include "Pipeline.h"

#include "Device.h"

namespace Wraith {
    Pipeline::Pipeline(Device& device, VkPipeline pipeline, VkPipelineLayout pipelineLayout)
        : _device(device), _pipeline(pipeline), _pipelineLayout(pipelineLayout) {}

    Pipeline::~Pipeline() {
        vkDestroyPipeline(_device.GetVkDevice(), _pipeline, nullptr);
        vkDestroyPipelineLayout(_device.GetVkDevice(), _pipelineLayout, nullptr);
    }

    void Pipeline::Bind(VkCommandBuffer commandBuffer) const {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline);
    }
}
