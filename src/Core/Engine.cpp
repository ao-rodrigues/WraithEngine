//
// Engine.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "Engine.h"
#include "wrpch.h"

#include <glm/gtx/transform.hpp>

#include "Asset/AssetManager.h"

#include "Core/Logger.h"

#include "Core/TimeManager.h"

#include "Platform/SDL2Window.h"

#include "Input/InputManager.h"

#include "Graphics/Mesh.h"
#include "Graphics/Pipeline.h"
#include "Graphics/Renderer.h"
#include "Graphics/Vulkan.h"

#include "Graphics/VkFactory.h"

namespace Wraith
{
    void Engine::Init(const EngineInitParams& initParams)
    {
        Logger::Init();

        WR_LOG_DEBUG("Staring Wraith Engine...")

        TimeManager::GetInstance().Init();

        m_Window = std::make_unique<SDL2Window>();
        m_Window->Create(initParams.WindowWidth, initParams.WindowHeight, initParams.WindowTitle);

        m_Device.Create(*m_Window);
        Renderer::GetInstance().Init(m_Device, *m_Window);

        InitPipelines();
        LoadMeshes();
        InitScene();
    }

    void Engine::Shutdown()
    {
        m_Device.FinishOperations();

        m_MainDeletionQueue.Flush();

        m_MeshPipeline.reset();

        m_Materials.clear();
        m_Meshes.clear();
        m_Renderables.clear();

        m_Device.Destroy();
        m_Window->Destroy();

        Logger::Shutdown();
    }

    void Engine::Run()
    {
        while (!m_Window->ShouldClose())
        {
            InputManager::GetInstance().ClearFrameEvents();
            TimeManager::GetInstance().Update();
            m_Window = nullptr;
            m_Window->PollEvents();

            UpdateLogic();
            Renderer::GetInstance().RenderFrame([=](VkCommandBuffer commandBuffer)
            {
                DrawRenderables(commandBuffer, m_Renderables);
            });
        }
        Shutdown();
    }

    DeletionQueue& Engine::GetMainDeletionQueue()
    {
        return m_MainDeletionQueue;
    }

    std::shared_ptr<Material> Engine::CreateMaterial(std::shared_ptr<Pipeline> pipeline, const std::string& name)
    {
        m_Materials[name] = std::make_shared<Material>(Material{std::move(pipeline)});
        return m_Materials[name];
    }

    std::shared_ptr<Material> Engine::GetMaterial(const std::string& name)
    {
        auto it = m_Materials.find(name);
        return it != m_Materials.end() ? (*it).second : nullptr;
    }

    std::shared_ptr<Mesh> Engine::GetMesh(const std::string& name)
    {
        auto it = m_Meshes.find(name);
        return it != m_Meshes.end() ? (*it).second : nullptr;
    }

    void Engine::InitPipelines()
    {
        // Init shaders
        const VkShaderModule vertShaderModule = VkFactory::ShaderModule(m_Device.GetVkDevice(),
                                                                        WR_ASSET("shaders/SimpleShader.vert.spv"));
        const VkShaderModule fragShaderModule = VkFactory::ShaderModule(m_Device.GetVkDevice(),
                                                                        WR_ASSET("shaders/SimpleShader.frag.spv"));

        // Build pipeline
        Pipeline::Builder pipelineBuilder;
        pipelineBuilder.ShaderStages.emplace_back(
            VkFactory::PipelineShaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, vertShaderModule));
        pipelineBuilder.ShaderStages.emplace_back(
            VkFactory::PipelineShaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, fragShaderModule));

        const auto bindingDescriptions = Mesh::Vertex::GetBindingDescriptions();
        const auto attributeDescriptions = Mesh::Vertex::GetAttributeDescriptions();
        pipelineBuilder.VertexInputInfo = VkFactory::PipelineVertexInputStateCreateInfo(
            bindingDescriptions, attributeDescriptions);

        pipelineBuilder.InputAssembly = VkFactory::PipelineInputAssemblyStateCreateInfo(
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
        pipelineBuilder.ViewportState = VkFactory::PipelineViewportStateCreateInfo();
        pipelineBuilder.Rasterizer = VkFactory::PipelineRasterizationStateCreateInfo(VK_POLYGON_MODE_FILL);
        pipelineBuilder.Multisampling = VkFactory::PipelineMultisampleStateCreateInfo();

        const std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments = {
            VkFactory::PipelineColorBlendAttachmentState()
        };
        pipelineBuilder.ColorBlending = VkFactory::PipelineColorBlendStateCreateInfo(colorBlendAttachments);

        pipelineBuilder.DepthStencilInfo = VkFactory::DepthStencilStateCreateInfo(
            true, true, VK_COMPARE_OP_LESS_OR_EQUAL);

        const std::vector<VkDynamicState> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        pipelineBuilder.DynamicState = VkFactory::PipelineDynamicStateCreateInfo(dynamicStates);


        const std::vector<VkPushConstantRange> pushConstantRanges = {
            VkFactory::PushConstantRange(0, sizeof(Mesh::PushConstants), VK_SHADER_STAGE_VERTEX_BIT)
        };
        VkPipelineLayoutCreateInfo meshPipelineLayoutInfo = VkFactory::PipelineLayoutCreateInfo(pushConstantRanges);
        VkPipelineLayout meshPipelineLayout;
        WR_VK_CHECK_MSG(
            vkCreatePipelineLayout(m_Device.GetVkDevice(), &meshPipelineLayoutInfo, nullptr, &meshPipelineLayout),
            "Failed to create pipeline layout!")

        pipelineBuilder.PipelineLayout = meshPipelineLayout;

        m_MeshPipeline = std::make_shared<Pipeline>(
            m_Device, pipelineBuilder.Build(m_Device.GetVkDevice(), Renderer::GetInstance().GetRenderPass()),
            meshPipelineLayout);

        vkDestroyShaderModule(m_Device.GetVkDevice(), vertShaderModule, nullptr);
        vkDestroyShaderModule(m_Device.GetVkDevice(), fragShaderModule, nullptr);

        CreateMaterial(m_MeshPipeline, "M_Default");
    }

    void Engine::LoadMeshes()
    {
        m_Meshes["Monke"] = std::make_shared<Mesh>(m_Device, WR_ASSET("Suzanne.gltf"));
        m_Meshes["Duck"] = std::make_shared<Mesh>(m_Device, WR_ASSET("Duck.glb"), true);
    }

    void Engine::InitScene()
    {
        Renderable monke;
        monke.Mesh = GetMesh("Monke");
        monke.Material = GetMaterial("M_Default");
        monke.Transform = glm::mat4{1.0f} * glm::translate(glm::mat4{1.0f}, glm::vec3(0, 5, 0));

        m_Renderables.emplace_back(monke);

        for (int x = -20; x <= 20; x += 2)
        {
            for (int y = -20; y <= 20; y += 2)
            {
                Renderable duck;
                duck.Mesh = GetMesh("Duck");
                duck.Material = GetMaterial("M_Default");

                glm::mat4 translation = glm::translate(glm::mat4{1.0f}, glm::vec3(x, 0, y));
                glm::mat4 scale = glm::scale(glm::mat4{1.0}, glm::vec3(0.01f, 0.01f, 0.01f));
                duck.Transform = translation * scale;

                m_Renderables.emplace_back(duck);
            }
        }
    }

    void Engine::UpdateLogic()
    {
        float movementSpeed = 12.0f;
        static constexpr float k_TurboMultiplier = 2.5f;

        if (Input::IsKeyDown(Input::EKeyCode::LShift))
        {
            movementSpeed *= k_TurboMultiplier;
        }
        if (Input::IsKeyDown(Input::EKeyCode::W))
        {
            m_CameraPos += m_CameraFront * movementSpeed * static_cast<float>(Time::GetDeltaTime());
        }
        else if (Input::IsKeyDown(Input::EKeyCode::S))
        {
            m_CameraPos -= m_CameraFront * movementSpeed * static_cast<float>(Time::GetDeltaTime());
        }

        if (Input::IsKeyDown(Input::EKeyCode::D))
        {
            m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * movementSpeed * (float)
                Time::GetDeltaTime();
        }
        else if (Input::IsKeyDown(Input::EKeyCode::A))
        {
            m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * movementSpeed * (float)
                Time::GetDeltaTime();
        }

        static constexpr float k_Sensitivity = 160.0f;
        const glm::vec2 mouseDelta = Input::GetMouseDelta();
        m_CameraLook.x += mouseDelta.x * k_Sensitivity * (float)Time::GetDeltaTime();
        m_CameraLook.y -= mouseDelta.y * k_Sensitivity * (float)Time::GetDeltaTime();

        if (m_CameraLook.y > 89.0f)
        {
            m_CameraLook.y = 89.0f;
        }
        else if (m_CameraLook.y < -89.0f)
        {
            m_CameraLook.y = -89.0f;
        }

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_CameraLook.x)) * cos(glm::radians(m_CameraLook.y));
        direction.y = sin(glm::radians(m_CameraLook.y));
        direction.z = sin(glm::radians(m_CameraLook.x)) * cos(glm::radians(m_CameraLook.y));
        m_CameraFront = glm::normalize(direction);

        static constexpr float k_ZoomSpeed = 5500.0f;
        float zoom = Input::GetMouseWheel().y;
        m_Fov -= zoom * k_ZoomSpeed * static_cast<float>(Time::GetDeltaTime());
        m_Fov = std::clamp(m_Fov, 1.0f, 70.0f);
    }

    void Engine::DrawRenderables(VkCommandBuffer commandBuffer, const std::vector<Renderable>& renderables)
    {
        const glm::mat4 view = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);

        const VkExtent2D windowExtent = m_Window->GetExtent();
        glm::mat4 projection = glm::perspective(glm::radians(m_Fov),
                                                static_cast<float>(windowExtent.width) / static_cast<float>(windowExtent
                                                    .height), 0.1f, 200.0f);
        projection[1][1] *= -1;

        std::shared_ptr<Mesh> lastMesh = nullptr;
        std::shared_ptr<Material> lastMaterial = nullptr;
        for (const auto& renderable : renderables)
        {
            // Only bind the pipeline if it doesn't match with the one already bound
            if (renderable.Material != lastMaterial)
            {
                renderable.Material->Pipeline->Bind(commandBuffer);
                lastMaterial = renderable.Material;
            }

            glm::mat4 model = renderable.Transform;
            glm::mat4 meshMatrix = projection * view * model;

            Mesh::PushConstants pushConstants{};
            pushConstants.RenderMatrix = meshMatrix;

            vkCmdPushConstants(commandBuffer, renderable.Material->Pipeline->GetPipelineLayout(),
                               VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(Mesh::PushConstants), &pushConstants);

            // Only bind the mesh if it's different from last bind
            if (renderable.Mesh != lastMesh)
            {
                renderable.Mesh->Bind(commandBuffer);
                lastMesh = renderable.Mesh;
            }

            renderable.Mesh->Draw(commandBuffer);
        }
    }
}
