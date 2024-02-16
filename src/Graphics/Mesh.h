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
            glm::vec4 Data;
            glm::mat4 RenderMatrix;
        };

        struct Vertex {
            glm::vec3 Position;
            glm::vec3 Color;

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

        Device& m_Device;

        VmaAllocation m_VertexBufferAllocation = VK_NULL_HANDLE;
        VkBuffer m_VertexBuffer = VK_NULL_HANDLE;
        uint32_t m_VertexCount = 0;


        VmaAllocation m_IndexBufferAllocation = VK_NULL_HANDLE;
        VkBuffer m_IndexBuffer = VK_NULL_HANDLE;
        uint32_t m_IndexCount = 0;
    };
}
