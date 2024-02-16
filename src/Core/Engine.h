//
// Engine.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include "Utils/DeletionQueue.h"
#include "Utils/Singleton.h"

#include "Platform/Window.h"

#include "Graphics/Device.h"
#include "Graphics/Swapchain.h"
#include "Graphics/Pipeline.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Renderable.h"

#include "Graphics/Renderer.h"

namespace Wraith
{
    struct EngineInitParams
    {
        int WindowWidth;
        int WindowHeight;
        std::string WindowTitle;
    };

    class Engine final : public Singleton<Engine>
    {
    public:
        void Init(const EngineInitParams& initParams);
        void Run();
        void Shutdown();

        DeletionQueue& GetMainDeletionQueue();

        std::shared_ptr<Material> CreateMaterial(std::shared_ptr<Pipeline> pipeline, const std::string& name);
        std::shared_ptr<Material> GetMaterial(const std::string& name);

        std::shared_ptr<Mesh> GetMesh(const std::string& name);

    private:
        void InitPipelines();
        void LoadMeshes();
        void InitScene();

        void UpdateLogic();
        void DrawRenderables(VkCommandBuffer commandBuffer, const std::vector<Renderable>& renderables);

        std::unique_ptr<Window> m_Window;
        Device m_Device;
        std::shared_ptr<Pipeline> m_MeshPipeline;

        DeletionQueue m_MainDeletionQueue;

        std::unordered_map<std::string, std::shared_ptr<Material>> m_Materials;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_Meshes;
        std::vector<Renderable> m_Renderables;

        glm::vec3 m_CameraPos {0.0f, 5.0f, 8.0f};
        glm::vec3 m_CameraFront {0.0f, 0.0f, -1.0f};
        glm::vec3 m_CameraUp {0.0f, 1.0f, 0.0f};

        glm::vec2 m_CameraLook {-90.0f, 0.0f};
        float m_Fov = 70.0f;
    };

#define WRAITH_ENGINE ::Wraith::Engine::Instance()
}
