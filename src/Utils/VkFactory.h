//
// Created by Andre Rodrigues on 16/06/2022.
//

#pragma once

#include "Core/VulkanBase.h"

namespace Wraith::VkFactory {
    VkShaderModule ShaderModule(VkDevice device, const std::string& shaderPath);

    // Pipeline creation factories
    VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule shaderModule);
    VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo(const std::vector<VkVertexInputBindingDescription>& bindingDescriptions, const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions);
    VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology topology);
    VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo();
    VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo(VkPolygonMode polygonMode);
    VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo();
    VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState();
    VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(const std::vector<VkDynamicState>& dynamicStates);

    // Image creation
    VkImageCreateInfo ImageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent);
    VkImageViewCreateInfo ImageViewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags);


    VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo(bool depthTest, bool depthWrite, VkCompareOp compareOp);
}