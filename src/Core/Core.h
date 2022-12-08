#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "Wraith/Logger.h"
#include "Utils.h"


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
