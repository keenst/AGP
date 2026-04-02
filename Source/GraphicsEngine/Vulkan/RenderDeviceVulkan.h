#pragma once

#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"
#include "../RenderDevice.h"

class RenderDeviceVulkan : public RenderDevice
{
public:
	RenderDeviceVulkan();
	RenderDeviceVulkan(VkInstance aInstance, VkSurfaceKHR aSurface, PFN_vkGetInstanceProcAddr aVkGetInstanceProcAddr);
	~RenderDeviceVulkan();

	virtual bool Init(int aWidth, int aHeight, bool aFullscreen, bool aVSync) override;
    virtual bool Destroy() override;

    virtual bool Begin() override;
    virtual void End() override;

    virtual PipelineID CreatePipeline(const PipelineState& aPipelineState) override;
    virtual void BindPipeline(const PipelineID aPipelineID) override;

    virtual ShaderID CreateShader(const ShaderInfo& aShaderInfo) override;
    virtual VertexLayoutID CreateVertexLayout(const std::vector<InputLayoutElement>& aInputLayoutElements) override;

    virtual VertexBufferID CreateVertexBuffer(const int aSizeInBytes, const void* aData) override;
    virtual void BindVertexBuffer(VertexBufferID aVertexBufferID, unsigned int aStride, unsigned int aOffset) override;

    virtual IndexBufferID CreateIndexBuffer(IndexBufferFormat aFormat, const int aSizeInBytes, const void* aData) override;
    virtual void BindIndexBuffer(IndexBufferID aIndexBufferID) override;

    virtual void Draw(bool aUseIndexBuffer, int aIndexCount, int aInstances) override;

    virtual void SetPushConstant(int aSizeInBytes, void* aData) override; 

    virtual BufferID CreateConstantBuffer(int aSizeInBytes, int aSlot) override;
    virtual void SetConstantBuffer(BufferID aBufferID, ShaderType aShaderType) override;
    virtual bool SetBufferData(BufferID aBufferID, int aSizeInBytes, void* aData) override;
private:
	VkInstance myInstance;
	VkSurfaceKHR mySurface;
	PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
};
