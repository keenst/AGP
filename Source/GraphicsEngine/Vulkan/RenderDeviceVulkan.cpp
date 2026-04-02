#include <assert.h>
#include "RenderDeviceVulkan.h"

#define VK_LOAD_FUNC(lib, func) \
	func = (PFN_##func)GetProcAddress(lib, "##func"); \
	assert(func);

#define VK_DECLARE_FUNC(func) PFN_##func func

#define VK_ASSERT(func) \
{ \
	VkResult r = func; \
	assert(r == VK_SUCCESS); \
}

VK_DECLARE_FUNC(vkCreateInstance);

RenderDeviceVulkan::RenderDeviceVulkan(
		VkInstance aInstance,
		VkSurfaceKHR aSurface,
		PFN_vkGetInstanceProcAddr aVkGetInstanceProcAddr)
{
	myInstance = aInstance;
	mySurface = aSurface;
	vkGetInstanceProcAddr = aVkGetInstanceProcAddr;
}

RenderDeviceVulkan::~RenderDeviceVulkan()
{
}

bool RenderDeviceVulkan::Init(int aWidth, int aHeight, bool aFullscreen, bool aVSync)
{
	return false;
}

bool RenderDeviceVulkan::Destroy()
{
	return false;
}

bool RenderDeviceVulkan::Begin()
{
	return false;
}

void RenderDeviceVulkan::End()
{
}

PipelineID RenderDeviceVulkan::CreatePipeline(const PipelineState& aPipelineState)
{
	return 0;
}

void RenderDeviceVulkan::BindPipeline(const PipelineID aPipelineID)
{
}

ShaderID RenderDeviceVulkan::CreateShader(const ShaderInfo& aShaderInfo)
{
	return 0;
}

VertexLayoutID RenderDeviceVulkan::CreateVertexLayout(const std::vector<InputLayoutElement>& aInputLayoutElements)
{
	return 0;
}

VertexBufferID RenderDeviceVulkan::CreateVertexBuffer(const int aSizeInBytes, const void* aData)
{
	return 0;
}

void RenderDeviceVulkan::BindVertexBuffer(VertexBufferID aVertexBufferID, unsigned int aStride, unsigned int aOffset)
{
}

IndexBufferID RenderDeviceVulkan::CreateIndexBuffer(IndexBufferFormat aFormat, const int aSizeInBytes, const void* aData)
{
	return 0;
}

void RenderDeviceVulkan::BindIndexBuffer(IndexBufferID aIndexBufferID)
{
}

void RenderDeviceVulkan::Draw(bool aUseIndexBuffer, int aIndexCount, int aInstances)
{
}

void RenderDeviceVulkan::SetPushConstant(int aSizeInBytes, void* aData)
{
}

BufferID RenderDeviceVulkan::CreateConstantBuffer(int aSizeInBytes, int aSlot)
{
	return 0;
}

void RenderDeviceVulkan::SetConstantBuffer(BufferID aBufferID, ShaderType aShaderType)
{
}

bool RenderDeviceVulkan::SetBufferData(BufferID aBufferID, int aSizeInBytes, void* aData)
{
	return false;
}
