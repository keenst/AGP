#include "RenderDevice.h"
#include <algorithm>
#include <vector>
#include "ResourceID.h"

RenderDevice::RenderDevice()
{
	myVsyncEnabled = false;
	myVideoCardMemory = 0;
	myViewport = {};
	myClearColor = {};
	myAPI = "None"; //Headless or make this class abstract??
}

RenderDevice::~RenderDevice()
{
}

bool RenderDevice::Init(int aWidth, int aHeight, bool aFullscreen, bool  aVsync)
{
	aWidth;
	aHeight;
	myIsFullscreen = aFullscreen;
	myVsyncEnabled = aVsync;
	return true;
}

void RenderDevice::SetRenderSize(Vector2i aSize)
{
	aSize;
}

Vector2i RenderDevice::GetRenderSize() const
{
	return Vector2i();
}

bool RenderDevice::Destroy()
{


	return true;
}

void RenderDevice::SetClearColor(Color aColor)
{
	myClearColor = aColor;
}

Color RenderDevice::GetClearColor()
{
	return myClearColor;
}

bool RenderDevice::Begin()
{
	return true;
}


void RenderDevice::End()
{
	
}




PipelineID RenderDevice::CreatePipeline(const PipelineState& aPipelineState)
{
	aPipelineState;
	return PipelineID();
}

void RenderDevice::BindPipeline(PipelineID aPipelineID)
{
	aPipelineID;
}

const std::string& RenderDevice::GetLastError() const
{
	return myError;
}

const std::string& RenderDevice::GetVideoCardDescription() const
{
	return myVideoCardDescription;
}

int RenderDevice::GetVideoCardMemory() const
{
	return myVideoCardMemory;
}

const std::string& RenderDevice::GetRenderAPI() const
{
	return myAPI;
}

const Viewport& RenderDevice::GetViewport() const
{
	return myViewport;
}


Vector2i RenderDevice::GetScreenSize() const
{
	return Vector2i();
}

ShaderID RenderDevice::CreateShader(const ShaderInfo& aShaderInfo)
{
	aShaderInfo;
	return ShaderID();
}

VertexLayoutID RenderDevice::CreateVertexLayout(const std::vector<InputLayoutElement>& aInputLayoutElements)
{
	aInputLayoutElements;
	return -1;
}

VertexBufferID RenderDevice::CreateVertexBuffer(const int aSizeInBytes, const void* aData)
{
	aSizeInBytes;
	aData;
	assert(false);
	return VertexBufferID();
}

void RenderDevice::BindVertexBuffer(VertexBufferID aVertexBufferID, unsigned int aStride, unsigned int aOffset)
{
	aVertexBufferID;
	aStride;
	aOffset;
	assert(false);
}

IndexBufferID RenderDevice::CreateIndexBuffer(IndexBufferFormat aFormat, const int aSizeInBytes, const void* aData)
{
	aFormat;
	aSizeInBytes;
	aData;
	return IndexBufferID();
}




