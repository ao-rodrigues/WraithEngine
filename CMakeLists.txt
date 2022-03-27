cmake_minimum_required(VERSION 3.21)

project(WraithEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if (NOT DEFINED ASSETS_DIR)
    set(ASSETS_DIR assets)
endif ()

# External Libraries
# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW docs" FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL "Build GLFW tests" FORCE)
add_subdirectory(external/glfw)

# GLM
set(GLM_TEST_ENABLE OFF CACHE BOOL "Enable GLM tests" FORCE)
add_subdirectory(external/glm)

# spdlog
set(SPDLOG_MASTER_PROJECT OFF CACHE BOOL "" FORCE)
add_subdirectory(external/spdlog)

# VMA
add_subdirectory(external/VulkanMemoryAllocator)

# Vulkan
find_package(Vulkan REQUIRED)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
            glm
            spdlog
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_CURRENT_SOURCE_DIR}/include/WraithEngine
            ${Vulkan_INCLUDE_DIRS}
            glfw
            VulkanMemoryAllocator
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            glm
            spdlog::spdlog
        PRIVATE
            ${Vulkan_LIBRARIES}
            glfw
            VulkanMemoryAllocator
)

# Preprocessor defines
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DWR_CONFIG_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DWR_CONFIG_RELEASE")

target_precompile_headers(${PROJECT_NAME} PRIVATE src/wrpch.h)


