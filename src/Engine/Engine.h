#pragma once

#include "Singleton.h"

#include "Platform/Window.h"

#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Graphics/Pipeline.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Renderable.h"

#include "Renderer/Renderer.h"

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

        std::shared_ptr<Material> CreateMaterial(std::shared_ptr<Pipeline> pipeline, const std::string& name);
        std::shared_ptr<Material> GetMaterial(const std::string& name);

        std::shared_ptr<Mesh> GetMesh(const std::string& name);

    private:
        void InitPipelines();
        void LoadMeshes();
        void InitScene();

        void DrawRenderables(VkCommandBuffer commandBuffer, const std::vector<Renderable>& renderables);

        std::unique_ptr<Window> _window;
        std::unique_ptr<Device> _device;
        std::unique_ptr<SwapChain> _swapChain;
        std::shared_ptr<Pipeline> _meshPipeline;
        std::unique_ptr<Renderer> _renderer;

        std::unordered_map<std::string, std::shared_ptr<Material>> _materials;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> _meshes;
        std::vector<Renderable> _renderables;
    };

#define WRAITH_ENGINE ::Wraith::Engine::Instance()
}
