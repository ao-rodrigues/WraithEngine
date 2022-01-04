#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#define VULKAN_H // No need to include Vulkan since GLFW already did it
#include <VMA/vk_mem_alloc.h>