//
// Mesh.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"
#include "Mesh.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>

#include "Device.h"

#include "Core/Assert.h"

namespace Wraith
{
    std::vector<VkVertexInputBindingDescription> Mesh::Vertex::GetBindingDescriptions()
    {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> Mesh::Vertex::GetAttributeDescriptions()
    {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, Position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, Color);
        return attributeDescriptions;
    }

    Mesh::Mesh(Device& device, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
        : m_Device(device)
    {
        CreateVertexBuffers(vertices);
        CreateIndexBuffers(indices);
    }

    Mesh::Mesh(Device& device, const std::string& modelPath, bool binaryFile) : m_Device(device)
    {
        tinygltf::TinyGLTF loader;
        tinygltf::Model model;

        std::string err;
        std::string warn;
        if (!binaryFile && !loader.LoadASCIIFromFile(&model, &err, &warn, modelPath))
        {
            WR_LOG_ERROR("Failed to parse glTF file {}. Error: {}", modelPath, err);
            return;
        }
        else if (binaryFile && !loader.LoadBinaryFromFile(&model, &err, &warn, modelPath))
        {
            WR_LOG_ERROR("Failed to parse glb file {}. Error: {}", modelPath, err);
            return;
        }
        if (!warn.empty())
        {
            WR_LOG_WARNING("TinyGLTF: {}", warn);
        }
        if (!err.empty())
        {
            WR_LOG_ERROR("TinyGLTF: {}", err);
        }

        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;
        for (const auto& mesh : model.meshes)
        {
            for (const auto& primitive : mesh.primitives)
            {
                const tinygltf::Accessor& verticesAccessor = model.accessors[primitive.attributes.at("POSITION")];
                const tinygltf::Accessor& colorsAccessor = model.accessors[primitive.attributes.at("NORMAL")];
                const tinygltf::Accessor& indicesAccessor = model.accessors[primitive.indices];

                const tinygltf::BufferView& verticesBufferView = model.bufferViews[verticesAccessor.bufferView];
                const tinygltf::BufferView& colorsBufferView = model.bufferViews[colorsAccessor.bufferView];
                const tinygltf::BufferView& indicesBufferView = model.bufferViews[indicesAccessor.bufferView];

                const tinygltf::Buffer& verticesBuffer = model.buffers[verticesBufferView.buffer];
                const tinygltf::Buffer& colorsBuffer = model.buffers[colorsBufferView.buffer];
                const tinygltf::Buffer& indicesBuffer = model.buffers[indicesBufferView.buffer];

                // Add vertex data
                const auto* vertexData = reinterpret_cast<const float*>(&verticesBuffer.data[verticesBufferView.
                    byteOffset + verticesAccessor.byteOffset]);
                const auto* colorData = reinterpret_cast<const float*>(&colorsBuffer.data[colorsBufferView.byteOffset +
                    colorsAccessor.byteOffset]);
                for (size_t i = 0; i < verticesAccessor.count; ++i)
                {
                    Vertex vertex {
                        {
                            vertexData[i * 3 + 0],
                            vertexData[i * 3 + 1],
                            vertexData[i * 3 + 2]
                        },
                        {
                            colorData[i * 3 + 0],
                            colorData[i * 3 + 1],
                            colorData[i * 3 + 2]
                        }
                    };
                    vertices.emplace_back(vertex);
                }

                // Add index data
                const auto* indexData = reinterpret_cast<const uint16_t*>(&indicesBuffer.data[indicesBufferView.
                    byteOffset + indicesAccessor.byteOffset]);
                for (size_t i = 0; i < indicesAccessor.count; ++i)
                {
                    indices.emplace_back(indexData[i]);
                }
            }
        }

        CreateVertexBuffers(vertices);
        CreateIndexBuffers(indices);
    }

    Mesh::~Mesh()
    {
        vmaDestroyBuffer(m_Device.GetAllocator(), m_VertexBuffer, m_VertexBufferAllocation);
        vmaDestroyBuffer(m_Device.GetAllocator(), m_IndexBuffer, m_IndexBufferAllocation);
    }

    void Mesh::Bind(VkCommandBuffer commandBuffer)
    {
        const VkBuffer buffers[] = {
            m_VertexBuffer
        };
        const VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer, m_IndexBuffer, 0, VK_INDEX_TYPE_UINT16);
    }

    void Mesh::Draw(VkCommandBuffer commandBuffer)
    {
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(m_IndexCount), 1, 0, 0, 0);
    }

    void Mesh::CreateVertexBuffers(const std::vector<Vertex>& vertices)
    {
        m_VertexCount = static_cast<uint32_t>(vertices.size());
        WR_ASSERT_MSG(m_VertexCount >= 3, "Vertex count must be at least 3!")

        const VkDeviceSize bufferSize = sizeof(vertices[0]) * m_VertexCount;
        m_Device.CreateBuffer(
            bufferSize,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            m_VertexBuffer,
            VMA_MEMORY_USAGE_CPU_TO_GPU,
            m_VertexBufferAllocation
        );

        void* data;
        vmaMapMemory(m_Device.GetAllocator(), m_VertexBufferAllocation, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vmaUnmapMemory(m_Device.GetAllocator(), m_VertexBufferAllocation);
    }

    void Mesh::CreateIndexBuffers(const std::vector<uint16_t>& indices)
    {
        m_IndexCount = static_cast<uint32_t>(indices.size());
        const VkDeviceSize bufferSize = sizeof(indices[0]) * m_IndexCount;
        m_Device.CreateBuffer(
            bufferSize,
            VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
            m_IndexBuffer,
            VMA_MEMORY_USAGE_CPU_TO_GPU,
            m_IndexBufferAllocation
        );

        void* data;
        vmaMapMemory(m_Device.GetAllocator(), m_IndexBufferAllocation, &data);
        memcpy(data, indices.data(), static_cast<size_t>(bufferSize));
        vmaUnmapMemory(m_Device.GetAllocator(), m_IndexBufferAllocation);
    }
}
