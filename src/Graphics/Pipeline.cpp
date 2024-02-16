//
// Pipeline.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"
#include "Pipeline.h"

#include "Core/Logger.h"

namespace Wraith {

    VkPipeline Pipeline::Builder::Build(VkDevice device, VkRenderPass renderPass) {
        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = shaderStages.size();
        pipelineInfo.pStages = shaderStages.data();
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = &depthStencilInfo; // Optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = &dynamicState; // Optional
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
        pipelineInfo.basePipelineIndex = -1; // Optional

        VkPipeline newPipeline;
        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &newPipeline) != VK_SUCCESS) {
            WR_LOG_ERROR("Failed to create pipeline!")
            return VK_NULL_HANDLE;
        }
        return newPipeline;
    }

    Pipeline::Pipeline(const Device& device, VkPipeline pipeline, VkPipelineLayout pipelineLayout)
        : _device(device), _pipeline(pipeline), _pipelineLayout(pipelineLayout) {}

    Pipeline::~Pipeline() {
        vkDestroyPipeline(_device->GetVkDevice(), _pipeline, nullptr);
        vkDestroyPipelineLayout(_device->GetVkDevice(), _pipelineLayout, nullptr);
    }

    void Pipeline::Bind(VkCommandBuffer commandBuffer) const {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline);
    }
}
