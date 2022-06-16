//
// Created by Andre Rodrigues on 16/06/2022.
//

#pragma once

#include "Core/VulkanBase.h"

namespace Wraith::VkFactory {

    VkImageCreateInfo ImageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent);
    VkImageViewCreateInfo ImageViewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags);

}