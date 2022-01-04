#pragma once

#include "Core/VulkanBase.h"

namespace Wraith
{
	class Device;

	class Mesh
	{
	public:
		struct Vertex
		{
			glm::vec2 position;
			glm::vec3 color;
			
			static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
		};

		Mesh(Device& device, const std::vector<Vertex>& vertices);
		~Mesh();

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		void Bind(VkCommandBuffer commandBuffer);
		void Draw(VkCommandBuffer commandBuffer);

	private:
		void CreateVertexBuffers(const std::vector<Vertex>& vertices);

		Device& _device;
		VmaAllocation _vertexBufferAllocation;
		VkBuffer _vertexBuffer = VK_NULL_HANDLE;
		uint32_t _vertexCount;
	};
}
