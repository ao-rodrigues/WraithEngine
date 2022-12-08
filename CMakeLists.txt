cmake_minimum_required(VERSION 3.21)

project(WraithEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# External Libraries
# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW docs" FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL "Build GLFW tests" FORCE)
add_subdirectory(libs/glfw)

# SDL2
set(SDL_SHARED ON CACHE BOOL "Build SDL shared")
set(SDL_STATIC OFF CACHE BOOL "Build SDL static")
add_subdirectory(libs/SDL2)

# GLM
set(GLM_TEST_ENABLE OFF CACHE BOOL "Enable GLM tests" FORCE)
add_subdirectory(libs/glm)

# tinygltf
set(TINYGLTF_HEADER_ONLY ON CACHE INTERNAL "" FORCE)
set(TINYGLTF_INSTALL OFF CACHE INTERNAL "" FORCE)
add_subdirectory(libs/tinygltf)

# spdlog
set(SPDLOG_MASTER_PROJECT OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/spdlog)

# VMA
add_subdirectory(libs/VulkanMemoryAllocator)

# Vulkan
find_package(Vulkan REQUIRED COMPONENTS glslc)
find_program(GLSLC_EXECUTABLE NAMES glslc HINTS Vulkan::glslc)

add_library(${PROJECT_NAME} STATIC
        ${PROJECT_SOURCE_DIR}/include/Wraith/Application.h
        ${PROJECT_SOURCE_DIR}/include/Wraith/Singleton.h
        ${PROJECT_SOURCE_DIR}/src/Core/Core.h
        ${PROJECT_SOURCE_DIR}/src/Core/Logger.cpp
        ${PROJECT_SOURCE_DIR}/src/Core/Logger.h
        ${PROJECT_SOURCE_DIR}/src/Core/Utils.h
        ${PROJECT_SOURCE_DIR}/src/Core/VulkanBase.cpp
        ${PROJECT_SOURCE_DIR}/src/Core/VulkanBase.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Application.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/Engine.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/Engine.h
        ${PROJECT_SOURCE_DIR}/src/Graphics/Device.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphics/Device.h
        ${PROJECT_SOURCE_DIR}/src/Graphics/Material.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphics/Material.h
        ${PROJECT_SOURCE_DIR}/src/Graphics/Mesh.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphics/Mesh.h
        ${PROJECT_SOURCE_DIR}/src/Graphics/Pipeline.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphics/Pipeline.h
        ${PROJECT_SOURCE_DIR}/src/Graphics/PipelineBuilder.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphics/PipelineBuilder.h
        ${PROJECT_SOURCE_DIR}/src/Graphics/Renderable.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphics/Renderable.h
        ${PROJECT_SOURCE_DIR}/src/Graphics/Swapchain.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphics/Swapchain.h
        ${PROJECT_SOURCE_DIR}/src/Platform/GLFWWindow.cpp
        ${PROJECT_SOURCE_DIR}/src/Platform/GLFWWindow.h
        ${PROJECT_SOURCE_DIR}/src/Platform/SDL2Window.cpp
        ${PROJECT_SOURCE_DIR}/src/Platform/SDL2Window.h
        ${PROJECT_SOURCE_DIR}/src/Graphics/Renderer.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphics/Renderer.h
        ${PROJECT_SOURCE_DIR}/src/Utils/VkFactory.cpp
        ${PROJECT_SOURCE_DIR}/src/Utils/VkFactory.h
        ${PROJECT_SOURCE_DIR}/src/wrpch.cpp
        ${PROJECT_SOURCE_DIR}/src/wrpch.h
        ${PROJECT_SOURCE_DIR}/include/Wraith/Input.h
        ${PROJECT_SOURCE_DIR}/src/Input/InputManager.cpp
        ${PROJECT_SOURCE_DIR}/src/Input/InputManager.h
        ${PROJECT_SOURCE_DIR}/src/Platform/SDL2Input.cpp
        ${PROJECT_SOURCE_DIR}/src/Platform/SDL2Input.h
        ${PROJECT_SOURCE_DIR}/include/Wraith/Time.h
        ${PROJECT_SOURCE_DIR}/src/Core/TimeManager.cpp
        ${PROJECT_SOURCE_DIR}/src/Core/TimeManager.h
        ${PROJECT_SOURCE_DIR}/include/Wraith/DeletionQueue.h
        ${PROJECT_SOURCE_DIR}/include/Wraith/Object.h
        ${PROJECT_SOURCE_DIR}/src/Platform/Window.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
            glm
            spdlog
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src
            ${PROJECT_SOURCE_DIR}/include
            ${Vulkan_INCLUDE_DIRS}
            glfw
            VulkanMemoryAllocator
            tinygltf
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            glm
            spdlog::spdlog
        PRIVATE
            ${Vulkan_LIBRARIES}
            glfw
            VulkanMemoryAllocator
            SDL2::SDL2
            SDL2::SDL2main
            tinygltf
)

target_precompile_headers(${PROJECT_NAME} PRIVATE src/wrpch.h)

# Copy SDL2 dll to the same folder as the executable
if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
            VERBATIM
    )
endif()

if (NOT DEFINED ASSETS_DIR)
    set(ASSETS_DIR assets)
    set(BINARY_ASSETS_DIR ${CMAKE_BINARY_DIR}/${ASSETS_DIR})
endif ()

# Preprocessor defines
target_compile_definitions(
        ${PROJECT_NAME} PUBLIC
        WR_ASSETS_DIR="${ASSETS_DIR}"
        TINYGLTF_USE_CPP14
        $<$<CONFIG:DEBUG>:WR_CONFIG_DEBUG>
        $<$<CONFIG:RELEASE>:WR_CONFIG_RELEASE>
)

# Copy new assets
file(GLOB_RECURSE GameAssets
        ${CMAKE_SOURCE_DIR}/${ASSETS_DIR}/*.gltf
        ${CMAKE_SOURCE_DIR}/${ASSETS_DIR}/*.glb
        ${CMAKE_SOURCE_DIR}/${ASSETS_DIR}/*.bin
        ${CMAKE_SOURCE_DIR}/${ASSETS_DIR}/*.png
        ${CMAKE_SOURCE_DIR}/${ASSETS_DIR}/*.jpg
        ${CMAKE_SOURCE_DIR}/${ASSETS_DIR}/*.jpeg
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${BINARY_ASSETS_DIR}
        COMMENT "Creating ${BINARY_ASSETS_DIR}"
)

foreach(asset IN LISTS GameAssets)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${asset}
            ${BINARY_ASSETS_DIR}
            VERBATIM
    )
endforeach()

# Compile shaders
set(SHADER_SOURCE_DIR ${PROJECT_SOURCE_DIR}/shaders)
set(SHADER_BINARY_DIR ${BINARY_ASSETS_DIR}/shaders)

file(GLOB_RECURSE Shaders
        ${SHADER_SOURCE_DIR}/*.vert
        ${SHADER_SOURCE_DIR}/*.frag
        ${SHADER_SOURCE_DIR}/*.comp
        ${SHADER_SOURCE_DIR}/*.geom
        ${SHADER_SOURCE_DIR}/*.tesc
        ${SHADER_SOURCE_DIR}/*.tese
        ${SHADER_SOURCE_DIR}/*.mesh
        ${SHADER_SOURCE_DIR}/*.task
        ${SHADER_SOURCE_DIR}/*.rgen
        ${SHADER_SOURCE_DIR}/*.rchit
        ${SHADER_SOURCE_DIR}/*.rmiss
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
        COMMENT "Creating ${SHADER_BINARY_DIR}"
)

foreach(shader IN LISTS Shaders)
    get_filename_component(FILENAME ${shader} NAME)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${GLSLC_EXECUTABLE} ${shader} -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
            DEPENDS ${shader} ${SHADER_BINARY_DIR}
            COMMENT "Compiling ${FILENAME}"
    )
endforeach()
