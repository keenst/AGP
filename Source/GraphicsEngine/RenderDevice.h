#pragma once

#include "Color.h"
#include <string>
#include <unordered_map>
#include "Viewport.h"
#include "math/Matrix.hpp"
#include "math/Vector.hpp"
#include "RendererCommons.h"
#include "ID.hpp"
#include "ShaderInfo.h"
#include "Collections/List.hpp"

//temp
using VertexLayoutID = int;

struct InputLayoutElement
{
    std::string name; //I DONT WANT THIS WHY IS IT HERE
    int index;
    LayoutFormat format;
    int slot;
    int offset;
    InputLayoutClass layoutClass;
    int stepRate; //never used??
};

struct BlendStateAttachment
{
    bool blendEnabled = false;
    Blend sourceBlend = Blend::Zero;
    Blend destBlend = Blend::Zero;
    BlendOp blendOp = BlendOp::Add;
    Blend sourceAlpha = Blend::Zero;
    Blend destAlpha = Blend::Zero;
    BlendOp blendOpAlpha = BlendOp::Add;
    bool writeToRed = true;
    bool writeToGreen = true;
    bool writeToBlue = true;
    bool writeToAlpha = true;

    //uint8_t          writeMask;

};

struct BlendState
{
    List<BlendStateAttachment> blendStateAttachments;
    float blendConstants[4] = {1.f,1.f,1.f,1.f};
    LogicOp logicOp = LogicOp::Nop;
    bool logicOpEnabled = false;
};

struct MultisampleState
{
    bool alphaToCoverageEnabled = false;
    bool alphaToOneEnabled = false;
};

struct DepthStencilState
{
    bool depthEnabled = false;
    int depthWriteMask; //what? turn on or of write to depth buffer -> can be a bool or for future with vulkan?
    CompareOperation depthCompareOp = CompareOperation::Always;
    bool stencilEnabled = false;
    bool stencilRead = false;
    bool stencilWrite = false;
    //other stencil operations to be added...
};

struct RasterizerState
{
    CullMode cullMode = CullMode::Back;
    float depthBiasClamp = 0.0f;
    float depthBiasConstant = 0.0f;
    bool depthBiasEnabled = false;
    bool depthClampEnabled = false;
    bool frontFaceIsClockwize = false;
    bool doWireframe = false;
};

struct SamplerState
{
    SamplerBorderColor	borderColor = SamplerBorderColor::FloatOpaqueBlack;
    CompareOperation	compareOperation = CompareOperation::Always;
    float	maxAnisotropy = 1.0f;
    float	lodBias = 0.0f;
    float	maxLOD = FLT_MAX;
    float	minLOD = 0.0f;
    SamplerMipmapMode   magFilter = SamplerMipmapMode::Nearest;
    SamplerMipmapMode   minFilter = SamplerMipmapMode::Nearest;
    SamplerMipmapMode   mipFilter = SamplerMipmapMode::Nearest;
    SamplerAddressMode  addressModeU = SamplerAddressMode::Repeat;
    SamplerAddressMode  addressModeV = SamplerAddressMode::Repeat;
    SamplerAddressMode  addressModeW = SamplerAddressMode::Repeat;
    bool    unnormalizedCoordinates = false;
    bool	anisotropyEnabled = false;
    bool	compareEnabled = false;

};


struct PipelineState
{
    ShaderID shaderID;
    PrimitiveTopology primitiveTopology;
    VertexLayoutID vertexLayoutID;
    RasterizerState* rasterizerState;
    DepthStencilState* depthStencilState;
    MultisampleState* multisampleState;
    BlendState* blendState;

    //this should be provided by the shader (reflection?)
    SamplerState* samplerState;
};


struct RenderDeviceState
{
    size_t windowHandle;
    size_t instanceHandle;
    int width;
    int height;
    bool fullscreen;
    bool vsync;
};


class RenderDevice
{

public:
	RenderDevice();
	virtual ~RenderDevice();

    virtual bool Init(int aWidth, int aHeight, bool aFullscreen, bool  aVsync);

    virtual void SetRenderSize(Vector2i aSize);
    virtual Vector2i GetRenderSize() const;

    virtual const Viewport& GetViewport() const;

    virtual Vector2i GetScreenSize() const;

    virtual bool Destroy();

    virtual void SetClearColor(Color aColor);
    virtual Color GetClearColor();

    virtual bool Begin();
    virtual void End();

    virtual PipelineID CreatePipeline(const PipelineState& aPipelineState);
    virtual void BindPipeline(PipelineID aPipelineID);


    virtual ShaderID CreateShader(const ShaderInfo& aShaderInfo);
    virtual VertexLayoutID CreateVertexLayout(const std::vector<InputLayoutElement>& aInputLayoutElements);

    virtual VertexBufferID CreateVertexBuffer(const int aSizeInBytes, const void* aData);
    virtual void BindVertexBuffer(VertexBufferID aVertexBufferID, unsigned int aStride, unsigned int aOffset);

    virtual IndexBufferID CreateIndexBuffer(IndexBufferFormat aFormat, const int aSizeInBytes, const void* aData);
    virtual void BindIndexBuffer(IndexBufferID aIndexBufferID) = 0;

    virtual void Draw(bool aUseIndexBuffer, int aIndexCount, int aInstances) = 0;
    


    virtual BufferID CreateConstantBuffer(int aSizeInBytes, int aSlot) = 0;
    virtual bool SetBufferData(BufferID aBufferID, int aSizeInBytes, void* aData) = 0;
    //in vulkan these are decided on in the pipeline this should be called bindCB? pushconstant? YOU DONT SET THE SHADER TYPE BECAUSE ITS IN THE PIPELINE!?
    virtual void SetConstantBuffer(BufferID aBufferID, ShaderType aShaderType) = 0;
    
    //ouch
    virtual void SetPushConstant(int aSizeInBytes, void* aData) = 0;

    virtual const std::string& GetVideoCardDescription() const;
    virtual int GetVideoCardMemory() const;
    virtual const std::string& GetRenderAPI() const;

    virtual const std::string& GetLastError() const;

protected:

    Color myClearColor;
    Matrix4f myTransform;
    Viewport myViewport;
    Vector2i myRenderSize;
    Vector2i myScreenSize;
    bool myVsyncEnabled;
    bool myIsFullscreen;
    int myVideoCardMemory;
    std::string myVideoCardDescription;
    std::string myError;
    std::string myAPI;

};

