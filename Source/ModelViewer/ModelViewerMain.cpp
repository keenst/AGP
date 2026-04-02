#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"

#include "GraphicsEngine/Vulkan/RenderDeviceVulkan.h"

RenderDevice* globalRenderDevice = nullptr;

extern "C" __declspec(dllexport)
void AppInit(VkInstance aInstance, VkSurfaceKHR aSurface, PFN_vkGetInstanceProcAddr aVkGetInstanceProcAddr)
{
	globalRenderDevice = new RenderDeviceVulkan(aInstance, aSurface, aVkGetInstanceProcAddr);
}

extern "C" __declspec(dllexport)
void AppUpdateAndRender()
{
	printf("Test\n");
}
