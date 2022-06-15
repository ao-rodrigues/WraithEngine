#pragma once

#include "Utils/Singleton.h"

#include "Platform/Window.h"

#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Graphics/Pipeline.h"
#include "Graphics/Mesh.h"

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

    private:
        std::unique_ptr<Window> _window;
        std::unique_ptr<Device> _device;
        std::unique_ptr<SwapChain> _swapChain;
        std::unique_ptr<Pipeline> _graphicsPipeline;
        std::unique_ptr<Renderer> _renderer;
        std::unique_ptr<Mesh> _mesh;
    };

#define WRAITH_ENGINE ::Wraith::Engine::Instance()
}
