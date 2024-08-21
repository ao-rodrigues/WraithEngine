local VulkanSDKPath = os.getenv("VULKAN_SDK")

IncludeDirs = {}
IncludeDirs["VulkanSDK"] = "%{VulkanSDKPath}/Include"

LibraryDirs = {}
LibraryDirs["VulkanSDK"] = "%{VulkanSDKPath}/Lib"

Libraries = {}
Libraries["Vulkan"] = "%{LibraryDirs.VulkanSDK}/vulkan-1.lib"
Libraries["VulkanUtils"] = "%{LibraryDirs.VulkanSDK}/Vklayer_utils.lib"

Libraries["ShaderC_Debug"] = "%{LibraryDirs.VulkanSDK}/shaderc_sharedd.lib"
Libraries["SPIRV_Cross_Debug"] = "%{LibraryDirs.VulkanSDK}/spirv-cross-cored.lib"
Libraries["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDirs.VulkanSDK}/spirv-cross-glsld.lib"
Libraries["SPIRV_Tools_Debug"] = "%{LibraryDirs.VulkanSDK}/SPIRV-Toolsd.lib"

Libraries["ShaderC_Release"] = "%{LibraryDirs.VulkanSDK}/shaderc_shared.lib"
Libraries["SPIRV_Cross_Release"] = "%{LibraryDirs.VulkanSDK}/spirv-cross-core.lib"
Libraries["SPIRV_Cross_GLSL_Release"] = "%{LibraryDirs.VulkanSDK}/spirv-cross-glsl.lib"