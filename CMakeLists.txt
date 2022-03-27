cmake_minimum_required(VERSION 3.21)

project(WraithEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

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

target_precompile_headers(${PROJECT_NAME} PRIVATE src/wrpch.h)

if (NOT DEFINED ASSETS_DIR)
    set(ASSETS_DIR assets)
endif ()

# Preprocessor defines
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DWR_CONFIG_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DWR_CONFIG_RELEASE")

target_compile_definitions(${PROJECT_NAME} PUBLIC WR_ASSETS_DIR="${ASSETS_DIR}")

# Shader compilation
file(GLOB SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag)

message(STATUS "Compiling shaders...")
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND mkdir -p ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\\${ASSETS_DIR}\\shaders
)

foreach(shader ${SHADERS})
    get_filename_component(SHADER_NAME ${shader} NAME)
    message(STATUS "Compiling ${SHADER_NAME}...")
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND glslc -c ${shader} -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\\${ASSETS_DIR}\\shaders\\${SHADER_NAME}.spv
    )
endforeach()
message(STATUS "Shaders compiled!")
