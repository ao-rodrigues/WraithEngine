#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <memory>

#include "Logger.h"

#ifdef WR_CONFIG_DEBUG

#define WR_ASSERT(x, msg) if (!(x)) { WR_LOG_FATAL("[{}:{}] Assert {} failed: {}", __FILE__, __LINE__, #x, msg) }

#else

#define WR_ASSERT(x, msg)

#endif

