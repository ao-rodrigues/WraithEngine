#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "Core/Core.h"
#include "Device.h"

namespace Wraith
{
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
		VkBuffer _vertexBuffer = VK_NULL_HANDLE;
		VkDeviceMemory _vertexBufferMemory = VK_NULL_HANDLE;
		uint32_t _vertexCount;
	};
}
