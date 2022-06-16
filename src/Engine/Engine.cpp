#include "wrpch.h"
#include "Engine.h"

#include <glm/gtx/transform.hpp>

#include "Core/VulkanBase.h"
#include "Core/Utils.h"
#include "Platform/SDL2Window.h"

#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Graphics/Pipeline.h"
#include "Graphics/PipelineBuilder.h"
#include "Graphics/Mesh.h"

#include "Utils/VkFactory.h"

#include "Renderer/Renderer.h"

namespace Wraith {
    void Engine::Init(const EngineInitParams& initParams) {
        WRAITH_LOGGER.Init();
        WR_LOG_DEBUG("Staring Wraith Engine...")

        _window = std::make_unique<SDL2Window>(initParams.windowWidth, initParams.windowHeight, initParams.windowTitle);
        _device = std::make_unique<Device>(*_window);
        _swapChain = std::make_unique<SwapChain>(*_device, *_window);

        // Init shaders
        VkShaderModule vertShaderModule = VkFactory::ShaderModule(_device->GetDevice(),
                                                                  WR_ASSET("shaders/SimpleShader.vert.spv"));
        VkShaderModule fragShaderModule = VkFactory::ShaderModule(_device->GetDevice(),
                                                                  WR_ASSET("shaders/SimpleShader.frag.spv"));

        // Build pipeline
        PipelineBuilder pipelineBuilder;
        pipelineBuilder.shaderStages.emplace_back(
                VkFactory::PipelineShaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, vertShaderModule));
        pipelineBuilder.shaderStages.emplace_back(
                VkFactory::PipelineShaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, fragShaderModule));

        auto bindingDescriptions = Mesh::Vertex::GetBindingDescriptions();
        auto attributeDescriptions = Mesh::Vertex::GetAttributeDescriptions();
        pipelineBuilder.vertexInputInfo = VkFactory::PipelineVertexInputStateCreateInfo(bindingDescriptions, attributeDescriptions);

        pipelineBuilder.inputAssembly = VkFactory::PipelineInputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
        pipelineBuilder.viewportState = VkFactory::PipelineViewportStateCreateInfo();
        pipelineBuilder.rasterizer = VkFactory::PipelineRasterizationStateCreateInfo(VK_POLYGON_MODE_FILL);
        pipelineBuilder.multisampling = VkFactory::PipelineMultisampleStateCreateInfo();

        const std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments = {
                VkFactory::PipelineColorBlendAttachmentState()
        };
        pipelineBuilder.colorBlending = VkFactory::PipelineColorBlendStateCreateInfo(colorBlendAttachments);

        pipelineBuilder.depthStencilInfo = VkFactory::DepthStencilStateCreateInfo(true, true, VK_COMPARE_OP_LESS_OR_EQUAL);

        const std::vector<VkDynamicState> dynamicStates = {
                VK_DYNAMIC_STATE_VIEWPORT,
                VK_DYNAMIC_STATE_SCISSOR
        };
        pipelineBuilder.dynamicState = VkFactory::PipelineDynamicStateCreateInfo(dynamicStates);


        const std::vector<VkPushConstantRange> pushConstantRanges = {
                VkFactory::PushConstantRange(0, sizeof(Pipeline::MeshPushConstants), VK_SHADER_STAGE_VERTEX_BIT)
        };
        VkPipelineLayoutCreateInfo graphicsPipelineLayoutInfo = VkFactory::PipelineLayoutCreateInfo(pushConstantRanges);
        VkPipelineLayout  graphicsPipelineLayout;
        WR_VK_CHECK(vkCreatePipelineLayout(_device->GetDevice(), &graphicsPipelineLayoutInfo, nullptr, &graphicsPipelineLayout), "Failed to create pipeline layout!")
        pipelineBuilder.pipelineLayout = graphicsPipelineLayout;
        
        _graphicsPipeline = std::make_unique<Pipeline>(*_device, pipelineBuilder.Build(_device->GetDevice(), _swapChain->GetRenderPass()), graphicsPipelineLayout);
        _renderer = std::make_unique<Renderer>(*_device, *_window);

        /*
        std::vector<Mesh::Vertex> vertices = {
                {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f,  -0.5f}, {0.0f, 1.0f, 0.0f}},
                {{0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}},
                {{-0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}}
        };
        std::vector<uint16_t> indices = {
                0, 1, 2, 2, 3, 0
        };
        _mesh = std::make_unique<Mesh>(*_device, vertices, indices);
         */
        _mesh = std::make_unique<Mesh>(*_device, WR_ASSET("DamagedHelmet.glb"), true);
    }

    void Engine::Shutdown() {
        _device->FinishOperations();

        _renderer.reset();
        _graphicsPipeline.reset();
        _swapChain.reset();
        _mesh.reset();
        _device.reset();
        _window.reset();

        WRAITH_LOGGER.Shutdown();
    }

    void Engine::Run() {
        int frameNumber = 0;
        while (!_window->ShouldClose()) {
            _window->PollEvents();

            if (const VkCommandBuffer commandBuffer = _renderer->BeginFrame()) {
                _renderer->BeginSwapChainRenderPass(commandBuffer);

                _graphicsPipeline->Bind(commandBuffer);

                _mesh->Bind(commandBuffer);

                glm::vec3 camPos = {0.0f, 0.0f, -2.0f};
                glm::mat4 view = glm::translate(glm::mat4(1.0f), camPos);
                glm::mat4 projection = glm::perspective(glm::radians(70.0f), 1700.0f / 900.0f, 0.1f, 200.0f);
                projection[1][1] *= -1;

                glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<float>(frameNumber) * 0.04f), glm::vec3(0, 1, 0));

                glm::mat4 meshMatrix = projection * view * model;

                Pipeline::MeshPushConstants constants{};
                constants.renderMatrix = meshMatrix;

                vkCmdPushConstants(commandBuffer, _graphicsPipeline->GetPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(Pipeline::MeshPushConstants), &constants);

                _mesh->Draw(commandBuffer);

                _renderer->EndSwapChainRenderPass(commandBuffer);
                _renderer->EndFrame();
            }

            frameNumber++;
        }
        Shutdown();
    }
}
