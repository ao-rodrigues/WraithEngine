//
// Created by Andre Rodrigues on 16/06/2022.
//

#include "VkFactory.h"

namespace Wraith::VkFactory {

    VkImageCreateInfo ImageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent) {
        VkImageCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.imageType = VK_IMAGE_TYPE_2D;
        createInfo.format = format;
        createInfo.extent = extent;
        createInfo.mipLevels = 1;
        createInfo.arrayLayers = 1;
        createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        createInfo.usage = usageFlags;

        return createInfo;
    }

    VkImageViewCreateInfo ImageViewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags) {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = image;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = aspectFlags;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        return createInfo;
    }

    VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo(bool depthTest, bool depthWrite, VkCompareOp compareOp) {
        VkPipelineDepthStencilStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        createInfo.pNext = nullptr;

        createInfo.depthTestEnable = depthTest ? VK_TRUE : VK_FALSE;
        createInfo.depthWriteEnable = depthWrite ? VK_TRUE : VK_FALSE;
        createInfo.depthCompareOp = depthTest ? compareOp : VK_COMPARE_OP_ALWAYS;
        createInfo.depthBoundsTestEnable = VK_FALSE;
        createInfo.minDepthBounds = 0.0f; // Optional
        createInfo.maxDepthBounds = 1.0f; // Optional
        createInfo.stencilTestEnable = VK_FALSE;

        return createInfo;
    }

}

