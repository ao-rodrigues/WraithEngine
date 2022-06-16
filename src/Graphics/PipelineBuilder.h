//
// Created by Andre Rodrigues on 16/06/2022.
//

#pragma once

#include "Core/VulkanBase.h"

class Pipeline;

namespace Wraith {
    class PipelineBuilder {
    public:
        PipelineBuilder() = default;
        ~PipelineBuilder() = default;

        VkPipeline Build(VkDevice device, VkRenderPass renderPass);

        std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
        VkPipelineVertexInputStateCreateInfo vertexInputInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssembly;
        VkPipelineViewportStateCreateInfo viewportState;
        VkPipelineRasterizationStateCreateInfo rasterizer;
        VkPipelineMultisampleStateCreateInfo multisampling;
        VkPipelineColorBlendStateCreateInfo colorBlending;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineDynamicStateCreateInfo dynamicState;
        VkPipelineLayout pipelineLayout;
    };
}



