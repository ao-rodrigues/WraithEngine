//
// Pipeline.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"
#include "Pipeline.h"

#include "Core/Logger.h"

namespace Wraith
{
    VkPipeline Pipeline::Builder::Build(VkDevice device, VkRenderPass renderPass)
    {
        VkGraphicsPipelineCreateInfo pipelineInfo {};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = ShaderStages.size();
        pipelineInfo.pStages = ShaderStages.data();
        pipelineInfo.pVertexInputState = &VertexInputInfo;
        pipelineInfo.pInputAssemblyState = &InputAssembly;
        pipelineInfo.pViewportState = &ViewportState;
        pipelineInfo.pRasterizationState = &Rasterizer;
        pipelineInfo.pMultisampleState = &Multisampling;
        pipelineInfo.pDepthStencilState = &DepthStencilInfo; // Optional
        pipelineInfo.pColorBlendState = &ColorBlending;
        pipelineInfo.pDynamicState = &DynamicState; // Optional
        pipelineInfo.layout = PipelineLayout;
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
        pipelineInfo.basePipelineIndex = -1;              // Optional

        VkPipeline newPipeline;
        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &newPipeline) != VK_SUCCESS)
        {
            WR_LOG_ERROR("Failed to create pipeline!")
            return VK_NULL_HANDLE;
        }
        return newPipeline;
    }

    Pipeline::Pipeline(const Device& device, VkPipeline pipeline, VkPipelineLayout pipelineLayout)
        : m_Device(device), m_Pipeline(pipeline), m_PipelineLayout(pipelineLayout)
    {
    }

    Pipeline::~Pipeline()
    {
        vkDestroyPipeline(m_Device->GetVkDevice(), m_Pipeline, nullptr);
        vkDestroyPipelineLayout(m_Device->GetVkDevice(), m_PipelineLayout, nullptr);
    }

    void Pipeline::Bind(VkCommandBuffer commandBuffer) const
    {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline);
    }
}
