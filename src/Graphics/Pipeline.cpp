#include "wrpch.h"
#include "Pipeline.h"

#include "Device.h"
#include "Mesh.h"

namespace Wraith {
    Pipeline::Pipeline(Device& device, VkRenderPass renderPass, const std::string& vertShaderPath,
                       const std::string& fragShaderPath)
            : _device(device), _renderPass(renderPass) {
        const auto vertShaderCode = Utils::ReadFile(vertShaderPath);
        const auto fragShaderCode = Utils::ReadFile(fragShaderPath);

        _vertShaderModule = CreateShaderModule(vertShaderCode);
        _fragShaderModule = CreateShaderModule(fragShaderCode);

        CreateGraphicsPipeline();
    }

    Pipeline::~Pipeline() {
        vkDestroyShaderModule(_device.GetDevice(), _vertShaderModule, nullptr);
        vkDestroyShaderModule(_device.GetDevice(), _fragShaderModule, nullptr);
        vkDestroyPipeline(_device.GetDevice(), _pipeline, nullptr);
        vkDestroyPipelineLayout(_device.GetDevice(), _pipelineLayout, nullptr);
    }

    void Pipeline::Bind(VkCommandBuffer commandBuffer) const {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline);
    }

    void Pipeline::CreateGraphicsPipeline() {
        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = _vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = _fragShaderModule;
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {
                vertShaderStageInfo,
                fragShaderStageInfo
        };

        auto bindingDescriptions = Mesh::Vertex::GetBindingDescriptions();
        auto attributeDescriptions = Mesh::Vertex::GetAttributeDescriptions();

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data(); // Optional
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data(); // Optional

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        /*
        VkViewport viewport{};
        VkExtent2D swapChainExtent = _swapChain.GetExtent();
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(swapChainExtent.width);
        viewport.height = static_cast<float>(swapChainExtent.height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = swapChainExtent;
        */

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = nullptr;
        viewportState.scissorCount = 1;
        viewportState.pScissors = nullptr;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;
        rasterizer.depthBiasConstantFactor = 0.0f; // Optional
        rasterizer.depthBiasClamp = 0.0f; // Optional
        rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampling.minSampleShading = 1.0f; // Optional
        multisampling.pSampleMask = nullptr; // Optional
        multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
        multisampling.alphaToOneEnable = VK_FALSE; // Optional

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask =
                VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f; // Optional
        colorBlending.blendConstants[1] = 0.0f; // Optional
        colorBlending.blendConstants[2] = 0.0f; // Optional
        colorBlending.blendConstants[3] = 0.0f; // Optional


        const std::vector<VkDynamicState> dynamicStates = {
                VK_DYNAMIC_STATE_VIEWPORT,
                VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo dynamicState{};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.pDynamicStates = dynamicStates.data();
        dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = 0; // Optional
        pipelineLayoutCreateInfo.pSetLayouts = nullptr; // Optional

        VkPushConstantRange pushConstantRange{};
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(MeshPushConstants);
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        pipelineLayoutCreateInfo.pushConstantRangeCount = 1; // Optional
        pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange; // Optional

        if (vkCreatePipelineLayout(_device.GetDevice(), &pipelineLayoutCreateInfo, nullptr, &_pipelineLayout) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout!");
        }
        WR_LOG_DEBUG("Created pipeline layout.")

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = nullptr; // Optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = &dynamicState; // Optional
        pipelineInfo.layout = _pipelineLayout;
        pipelineInfo.renderPass = _renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
        pipelineInfo.basePipelineIndex = -1; // Optional

        if (vkCreateGraphicsPipelines(_device.GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_pipeline) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to create graphics pipeline!");
        }
        WR_LOG_DEBUG("Created graphics pipeline.")
    }

    VkShaderModule Pipeline::CreateShaderModule(const std::vector<char>& shaderCode) const {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = shaderCode.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(_device.GetDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module!");
        }
        return shaderModule;
    }
}
