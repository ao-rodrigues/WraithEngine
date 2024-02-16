//
// Pipeline.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include "Graphics/Device.h"
#include "Graphics/Vulkan.h"

namespace Wraith {

    class Pipeline {
    public:
        struct Builder {
            Builder() = default;
            ~Builder() = default;

            VkPipeline Build(VkDevice device, VkRenderPass renderPass);

            std::vector<VkPipelineShaderStageCreateInfo> ShaderStages;
            VkPipelineVertexInputStateCreateInfo VertexInputInfo;
            VkPipelineInputAssemblyStateCreateInfo InputAssembly;
            VkPipelineViewportStateCreateInfo ViewportState;
            VkPipelineRasterizationStateCreateInfo Rasterizer;
            VkPipelineMultisampleStateCreateInfo Multisampling;
            VkPipelineColorBlendStateCreateInfo ColorBlending;
            VkPipelineDepthStencilStateCreateInfo DepthStencilInfo;
            VkPipelineDynamicStateCreateInfo DynamicState;
            VkPipelineLayout PipelineLayout;
        };

        Pipeline(const Device& device, VkPipeline pipeline, VkPipelineLayout pipelineLayout);
        ~Pipeline();

        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(const Pipeline&) = delete;

        void Bind(VkCommandBuffer commandBuffer) const;

        VkPipeline GetVkPipeline() const { return m_Pipeline; }
        VkPipelineLayout GetPipelineLayout() const { return m_PipelineLayout; }

    private:
        Device::Ref m_Device;

        VkPipeline m_Pipeline = VK_NULL_HANDLE;
        VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;
    };
}
