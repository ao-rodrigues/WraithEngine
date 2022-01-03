#pragma once

#include <string>
#include <vector>

#include "Core/Core.h"
#include "Device.h"

namespace Wraith
{
	class Pipeline
	{
	public:
		struct ConfigInfo
		{
			
		};

		Pipeline(Device& device, VkRenderPass renderPass, const std::string& vertShaderPath, const std::string& fragShaderPath);
		~Pipeline();

		Pipeline(const Pipeline&) = delete;
		Pipeline& operator=(const Pipeline&) = delete;

		void Bind(VkCommandBuffer commandBuffer) const;

	private:
		void CreateGraphicsPipeline();
		VkShaderModule CreateShaderModule(const std::vector<char>& shaderCode) const;

		Device& _device;
		VkRenderPass _renderPass = VK_NULL_HANDLE;

		VkPipeline _pipeline = VK_NULL_HANDLE;
		VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
		VkShaderModule _vertShaderModule = VK_NULL_HANDLE;
		VkShaderModule _fragShaderModule = VK_NULL_HANDLE;
	};
}
