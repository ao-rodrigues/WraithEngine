#include "wrpch.h"
#include "Engine.h"

#include <glm/gtx/transform.hpp>

#include "Core/VulkanBase.h"
#include "Core/Utils.h"
#include "Core/TimeManager.h"

#include "Platform/SDL2Window.h"

#include "Input/InputManager.h"

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

        TimeManager::Instance().Init();

        _window = std::make_unique<SDL2Window>(initParams.windowWidth, initParams.windowHeight, initParams.windowTitle);
        _device = std::make_unique<Device>(*_window);
        _swapChain = std::make_unique<SwapChain>(*_device, *_window);
        _renderer = std::make_unique<Renderer>(*_device, *_window);

        InitPipelines();
        LoadMeshes();
        InitScene();
    }

    void Engine::Shutdown() {
        _device->FinishOperations();

        _renderer.reset();
        _meshPipeline.reset();
        _swapChain.reset();

        _materials.clear();
        _meshes.clear();
        _renderables.clear();

        _device.reset();
        _window.reset();

        WRAITH_LOGGER.Shutdown();
    }

    void Engine::Run() {
        while (!_window->ShouldClose()) {
            InputManager::Instance().ClearFrameEvents();
            TimeManager::Instance().Update();
            _window->PollEvents();

             // TODO Update game logic here

             // TODO Draw frame using single call from Renderer
            if (VkCommandBuffer commandBuffer = _renderer->BeginFrame()) {
                _renderer->BeginSwapChainRenderPass(commandBuffer);

                // TODO use ECS to get all entities with Renderable components
                DrawRenderables(commandBuffer, _renderables);

                _renderer->EndSwapChainRenderPass(commandBuffer);
                _renderer->EndFrame();
            }
        }
        Shutdown();
    }

    std::shared_ptr<Material> Engine::CreateMaterial(std::shared_ptr<Pipeline> pipeline, const std::string& name) {
        _materials[name] = std::make_shared<Material>(Material{std::move(pipeline)});
        return _materials[name];
    }

    std::shared_ptr<Material> Engine::GetMaterial(const std::string& name) {
        auto it = _materials.find(name);
        return it != _materials.end() ? (*it).second : nullptr;
    }

    std::shared_ptr<Mesh> Engine::GetMesh(const std::string& name) {
        auto it = _meshes.find(name);
        return it != _meshes.end() ? (*it).second : nullptr;
    }

    void Engine::InitPipelines() {
        // Init shaders
        VkShaderModule vertShaderModule = VkFactory::ShaderModule(_device->GetVkDevice(),
                                                                  WR_ASSET("shaders/SimpleShader.vert.spv"));
        VkShaderModule fragShaderModule = VkFactory::ShaderModule(_device->GetVkDevice(),
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
                VkFactory::PushConstantRange(0, sizeof(Mesh::PushConstants), VK_SHADER_STAGE_VERTEX_BIT)
        };
        VkPipelineLayoutCreateInfo meshPipelineLayoutInfo = VkFactory::PipelineLayoutCreateInfo(pushConstantRanges);
        VkPipelineLayout  meshPipelineLayout;
        WR_VK_CHECK(vkCreatePipelineLayout(_device->GetVkDevice(), &meshPipelineLayoutInfo, nullptr, &meshPipelineLayout), "Failed to create pipeline layout!")

        pipelineBuilder.pipelineLayout = meshPipelineLayout;

        _meshPipeline = std::make_shared<Pipeline>(*_device, pipelineBuilder.Build(_device->GetVkDevice(), _swapChain->GetRenderPass()), meshPipelineLayout);

        vkDestroyShaderModule(_device->GetVkDevice(), vertShaderModule, nullptr);
        vkDestroyShaderModule(_device->GetVkDevice(), fragShaderModule, nullptr);

        CreateMaterial(_meshPipeline, "M_Default");
    }

    void Engine::LoadMeshes() {
        _meshes["Monke"] = std::make_shared<Mesh>(*_device, WR_ASSET("Suzanne.gltf"));
        _meshes["Duck"] = std::make_shared<Mesh>(*_device, WR_ASSET("Duck.glb"), true);
    }

    void Engine::InitScene() {
        Renderable monke;
        monke.mesh = GetMesh("Monke");
        monke.material = GetMaterial("M_Default");
        monke.transform = glm::mat4{1.0f} * glm::translate(glm::mat4{1.0f}, glm::vec3(0, 5, 0));

        _renderables.emplace_back(monke);

        for (int x = -5; x <= 5; x++) {
            for (int y = -5; y <= 5; y++) {
                Renderable duck;
                duck.mesh = GetMesh("Duck");
                duck.material = GetMaterial("M_Default");

                glm::mat4 translation = glm::translate(glm::mat4{1.0f}, glm::vec3(x, 0, y));
                glm::mat4 scale = glm::scale(glm::mat4{1.0}, glm::vec3(0.01f, 0.01f, 0.01f));
                duck.transform = translation * scale;

                _renderables.emplace_back(duck);
            }
        }
    }

    void Engine::DrawRenderables(VkCommandBuffer commandBuffer, const std::vector<Renderable>& renderables) {
        glm::vec3 camPos = {0.0f, -6.0f, -10.0f};
        glm::mat4 view = glm::translate(glm::mat4(1.0f), camPos);

        VkExtent2D windowExtent = _window->GetExtent();
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), static_cast<float>(windowExtent.width) / static_cast<float>(windowExtent.height), 0.1f, 200.0f);
        projection[1][1] *= -1;

        std::shared_ptr<Mesh> lastMesh = nullptr;
        std::shared_ptr<Material> lastMaterial = nullptr;
        for(const auto& renderable : renderables) {
            // Only bind the pipeline if it doesn't match with the one already bound
            if (renderable.material != lastMaterial) {
                renderable.material->pipeline->Bind(commandBuffer);
                lastMaterial = renderable.material;
            }

            glm::mat4 model = renderable.transform;
            glm::mat4 meshMatrix = projection * view * model;

            Mesh::PushConstants pushConstants{};
            pushConstants.renderMatrix = meshMatrix;

            vkCmdPushConstants(commandBuffer, renderable.material->pipeline->GetPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(Mesh::PushConstants), &pushConstants);

            // Only bind the mesh if it's different from last bind
            if (renderable.mesh != lastMesh) {
                renderable.mesh->Bind(commandBuffer);
                lastMesh = renderable.mesh;
            }

            renderable.mesh->Draw(commandBuffer);
        }
    }
}
