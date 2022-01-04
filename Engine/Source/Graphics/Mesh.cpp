#include "wrpch.h"
#include "Mesh.h"

#include "Device.h"

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
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);
		return attributeDescriptions;
	}

	Mesh::Mesh(Device& device, const std::vector<Vertex>& vertices)
		: _device(device)
	{
		CreateVertexBuffers(vertices);
	}

	Mesh::~Mesh()
	{
		vmaDestroyBuffer(_device.GetAllocator(), _vertexBuffer, _vertexBufferAllocation);
	}

	void Mesh::Bind(VkCommandBuffer commandBuffer)
	{
		const VkBuffer buffers[] = {
			_vertexBuffer
		};
		const VkDeviceSize offsets[] = {0};
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
	}

	void Mesh::Draw(VkCommandBuffer commandBuffer)
	{
		vkCmdDraw(commandBuffer, _vertexCount, 1, 0, 0);
	}

	void Mesh::CreateVertexBuffers(const std::vector<Vertex>& vertices)
	{
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
}
