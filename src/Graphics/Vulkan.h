//
// Vulkan.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include <vulkan/vulkan.h>

#define VULKAN_H // No need to include Vulkan again
#include <vk_mem_alloc.h>

#include "Core/Logger.h"

#define WR_VK_CHECK(x)                                                          \
{                                                                               \
    VkResult err = x;                                                           \
    if (err != VK_SUCCESS) {                                                    \
        WR_LOG_ERROR("Vulkan error: {}", err);                                  \
        abort();                                                                \
    }                                                                           \
}                                                                               \


#define WR_VK_CHECK_MSG(x, msg)                                                 \
{                                                                               \
    VkResult err = x;                                                           \
    if (err != VK_SUCCESS) {                                                    \
        WR_LOG_ERROR("Vulkan error {}: {}", err, msg);                          \
        abort();                                                                \
    }                                                                           \
}                                                                               \
