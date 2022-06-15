#pragma once

#include "Core/VulkanBase.h"

namespace Wraith {
    class Device;

    class Pipeline {
    public:
        struct MeshPushConstants {
            glm::vec4 data;
            glm::mat4 renderMatrix;
        };

        Pipeline(Device& device, VkRenderPass renderPass, const std::string& vertShaderPath,
                 const std::string& fragShaderPath);
        ~Pipeline();

        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(const Pipeline&) = delete;

        void Bind(VkCommandBuffer commandBuffer) const;

        VkPipelineLayout GetPipelineLayout() const {return _pipelineLayout;}

    private:
        void CreateGraphicsPipeline();
        VkShaderModule CreateShaderModule(const std::vector<char>& shaderCode) const;

        Device& _device;
        VkRenderPass _renderPass = VK_NULL_HANDLE;

        VkPipeline _pipeline = VK_NULL_HANDLE;
        VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
        VkShaderModule _vertShaderModule = VK_NULL_HANDLE;
        VkShaderModule _fragShaderModule = VK_NULL_HANDLE;
    };
}
