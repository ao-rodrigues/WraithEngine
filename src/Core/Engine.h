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

namespace Wraith {
    struct EngineInitParams {
        int windowWidth;
        int windowHeight;
        std::string windowTitle;
    };

    class Engine final : public Singleton<Engine> {
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

        std::unique_ptr<Window> _window;
        Device _device;
        std::shared_ptr<Pipeline> _meshPipeline;

        DeletionQueue _mainDeletionQueue;

        std::unordered_map<std::string, std::shared_ptr<Material>> _materials;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> _meshes;
        std::vector<Renderable> _renderables;

        glm::vec3 _cameraPos {0.0f, 5.0f, 8.0f};
        glm::vec3 _cameraFront {0.0f, 0.0f, -1.0f};
        glm::vec3 _cameraUp {0.0f, 1.0f, 0.0f};

        glm::vec2 _cameraLook {-90.0f, 0.0f};
        float _fov = 70.0f;
    };

#define WRAITH_ENGINE ::Wraith::Engine::Instance()
}
