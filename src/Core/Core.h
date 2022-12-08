#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "Wraith/Logger.h"
#include "Utils.h"

#ifdef WR_CONFIG_DEBUG

#define WR_ASSERT(x)                            \
    if (!(x)) {                                 \
        WR_LOG_FATAL("Assert {} failed!");      \
        abort();                                \
    }                                           \

#define WR_ASSERT_MSG(x, msg)                                                           \
    if (!(x)) {                                                                         \
        WR_LOG_FATAL("[{}:{}] Assert {} failed: {}", __FILE__, __LINE__, #x, msg);      \
        abort();                                                                        \
    }                                                                                   \

#else

#define WR_ASSERT(x)
#define WR_ASSERT_MSG(x, msg)

#endif

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
