#pragma once

using IndexType = unsigned int;

enum class ShaderType
{
	Vertex,
	Fragment,
	Compute
};

enum class ShaderLanguage
{
	HLSL,
	GLSL,
	Slang,
	SPIRV
};

enum class SamplerBorderColor
{
	FloatTransparentBlack = 0,
	IntTransparentBlack,
	FloatOpaqueBlack,
	IntOpaqueBlack,
	FloatOpaqueWhite,
	IntOpaqueWhite
};

enum class PrimitiveTopology
{
	TriangleList = 0,
	TriangleStrip,
	LineList,
	LineStrip
};

enum class SamplerAddressMode
{
	Repeat = 0,
	Mirror,
	Clamp,
	Border
};

enum class CullMode
{
	None = 0,
	Front,
	Back,
	FrontAndBack
};

enum class FrontFaceWinding
{
	Clockwise,
	CounterClockwise
};

enum class FilterMode
{
	Nearest = 0,
	Linear
};

enum class SamplerMipmapMode
{
	Nearest = 0,
	Linear
};


enum class CompareOperation
{
	Never = 0,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always
};
enum class IndexBufferFormat
{
	Uint16,
	Uint32
};

enum class LayoutFormat
{
	R32G32B32A32_typeless,
	R32G32B32A32_float,
	R32G32B32A32_uint,
	R32G32B32A32_sint,
	R32G32B32_typeless,
	R32G32B32_float,
	R32G32B32_uint,
	R32G32B32_sint,
	R32G32_typeless,
	R32G32_float,
	R32G32_uint,
	R32G32_sint,
	R32_typeless,
	R32_float,
	R32_uint,
	R32_sint,
	D32_float, //depth float 32 same as R32(?) but drivers be like that
};

enum class InputLayoutClass
{
	PerVertexData,
	PerInstanceData
};

enum class  BlendOp
{
	Add = 0,
	Subtract = 1,
	ReverseSubtract = 2,
	Min = 3,
	Max = 4,
};

enum class Blend
{
	Zero,
	One,
	SourceColor,
	OneMinusSourceColor,
	DestColor,
	OneMinusDestColor,
	SourceAlpha,
	OneMinusSourceAlpha,
	DestAlpha,
	OneMinusDestAlpha,
	ConstantColor,
	OneMinusConstantColor,
	Source1Color,
	OneMinusSource1Color,
	Source1Alpha,
	OneMinusSource1Alpha,
	SourceAlphaSaturate,
	OneMinusSourceAlphaSaturate,
};

enum class LogicOp
{
	Clear = 0,
	And = 1,
	AndReverse = 2,
	Copy = 3,
	AndInverted = 4,
	Nop = 5,
	Xor = 6,
	Or = 7,
	Nor = 8,
	Equivalent = 9,
	Invert = 10,
	OrReverse = 11,
	CopyInverted = 12,
	OrInverted = 13,
	Nand = 14,
	Set = 15,
};

//below this is to be moved!

struct FrameConstantBuffer
{
	float width;
	float height;
	float deltaTime;
	float totalTime;
};

struct CameraConstantBuffer
{
	float viewMatrix[16];
	float projectionMatrix[16];
	float cameraPosition[3];
	float nearPlane;
	float cameraDirection[3];
	float farPlane;
};

struct LightConstantBuffer
{
	//nothing yet
};