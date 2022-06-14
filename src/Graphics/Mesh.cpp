#include "wrpch.h"
#include "Mesh.h"

#include "Device.h"

namespace Wraith {
    std::vector<VkVertexInputBindingDescription> Mesh::Vertex::GetBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> Mesh::Vertex::GetAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);
        return attributeDescriptions;
    }

    Mesh::Mesh(Device& device, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
            : _device(device) {
        CreateVertexBuffers(vertices);
        CreateIndexBuffers(indices);
    }

    Mesh::~Mesh() {
        vmaDestroyBuffer(_device.GetAllocator(), _vertexBuffer, _vertexBufferAllocation);
        vmaDestroyBuffer(_device.GetAllocator(), _indexBuffer, _indexBufferAllocation);
    }

    void Mesh::Bind(VkCommandBuffer commandBuffer) {
        const VkBuffer buffers[] = {
                _vertexBuffer
        };
        const VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer, _indexBuffer, 0, VK_INDEX_TYPE_UINT16);
    }

    void Mesh::Draw(VkCommandBuffer commandBuffer) {
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(_indexCount), 1, 0, 0, 0);
    }

    void Mesh::CreateVertexBuffers(const std::vector<Vertex>& vertices) {
        _vertexCount = static_cast<uint32_t>(vertices.size());
        WR_ASSERT(_vertexCount >= 3, "Vertex count must be at least 3!")

        const VkDeviceSize bufferSize = sizeof(vertices[0]) * _vertexCount;
        _device.CreateBuffer(
                bufferSize,
                VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                _vertexBuffer,
                VMA_MEMORY_USAGE_CPU_TO_GPU,
                _vertexBufferAllocation
        );

        void* data;
        vmaMapMemory(_device.GetAllocator(), _vertexBufferAllocation, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vmaUnmapMemory(_device.GetAllocator(), _vertexBufferAllocation);
    }

    void Mesh::CreateIndexBuffers(const std::vector<uint16_t>& indices) {
        _indexCount = static_cast<uint32_t>(indices.size());
        const VkDeviceSize bufferSize = sizeof(indices[0]) * _indexCount;
        _device.CreateBuffer(
                bufferSize,
                VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                _indexBuffer,
                VMA_MEMORY_USAGE_CPU_TO_GPU,
                _indexBufferAllocation
        );

        void* data;
        vmaMapMemory(_device.GetAllocator(), _indexBufferAllocation, &data);
        memcpy(data, indices.data(), static_cast<size_t>(bufferSize));
        vmaUnmapMemory(_device.GetAllocator(), _indexBufferAllocation);
    }
}
