#include "wrpch.h"
#include "Mesh.h"

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
		vkDestroyBuffer(_device.GetLogicalDevice(), _vertexBuffer, nullptr);
		vkFreeMemory(_device.GetLogicalDevice(), _vertexBufferMemory, nullptr);
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

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		_device.CreateBuffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,
			stagingBufferMemory
		);

		void* data;
		vkMapMemory(_device.GetLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(_device.GetLogicalDevice(), stagingBufferMemory);

		_device.CreateBuffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			_vertexBuffer,
			_vertexBufferMemory
		);

		// Copy to vertex buffer
		_device.CopyBuffer(stagingBuffer, _vertexBuffer, bufferSize);

		vkDestroyBuffer(_device.GetLogicalDevice(), stagingBuffer, nullptr);
		vkFreeMemory(_device.GetLogicalDevice(), stagingBufferMemory, nullptr);
	}
}
