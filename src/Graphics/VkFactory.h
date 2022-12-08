//
// VkFactory.h
// WraithEngine
//
// Created by Andre Rodrigues on 16/06/2022.
//

#pragma once

#include "Graphics/Vulkan.h"

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
    VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo(const std::vector<VkPipelineColorBlendAttachmentState>& colorBlendAttachments);
    VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(const std::vector<VkDynamicState>& dynamicStates);
    VkPushConstantRange PushConstantRange(uint32_t offset, uint32_t size, VkShaderStageFlags stageFlags);
    VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo(const std::vector<VkPushConstantRange>& pushConstantRanges);

    // Image creation
    VkImageCreateInfo ImageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent);
    VkImageViewCreateInfo ImageViewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags);

    VkFramebufferCreateInfo FramebufferCreateInfo(VkRenderPass renderPass, VkImageView* attachments, VkExtent2D swapChainExtent);

    // Sync structures
    VkFenceCreateInfo FenceCreateInfo();
    VkSemaphoreCreateInfo SemaphoreCreateInfo();

    VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo(bool depthTest, bool depthWrite, VkCompareOp compareOp);
}