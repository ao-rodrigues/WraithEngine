//
// Mesh.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include "Graphics/Vulkan.h"
#include "Math/Math.h"

namespace Wraith {
    class Device;

    class Mesh {
    public:
        struct PushConstants {
            glm::vec4 data;
            glm::mat4 renderMatrix;
        };

        struct Vertex {
            glm::vec3 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
        };

        Mesh(Device& device, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);
        Mesh(Device& device, const std::string& modelPath, bool binaryFile = false);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        void Bind(VkCommandBuffer commandBuffer);
        void Draw(VkCommandBuffer commandBuffer);

    private:
        void CreateVertexBuffers(const std::vector<Vertex>& vertices);
        void CreateIndexBuffers(const std::vector<uint16_t>& indices);

        Device& _device;

        AllocatedBuffer _vertexBuffer;
        uint32_t _vertexCount = 0;

        AllocatedBuffer _indexBuffer;
        uint32_t _indexCount = 0;
    };
}
