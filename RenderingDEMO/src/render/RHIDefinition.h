#pragma once

namespace RenderingDEMO
{
	enum class VertexElementType
	{
		None = 0,
		Float, 
		Float2, 
		Float3, 
		Float4, 
		UInt
	};

	enum class TextureFlags : unsigned int
	{
		TexRenderTarget = 1 << 0,
		TexDepthStencilTarget = 1 << 1,
		TexShaderResource = 1 << 2,
		TexGenMips = 1 << 3,
		TexImmutable = 1 << 4,
		TexDefault = 1 << 5,
		TexCubeMap = 1 << 6
	};

	enum class TextureFormat
	{
		Unknow = 0,
		R8_UNorm,
		R8G8_UNorm,
		R8G8B8A8_UNorm,
		R32_Typeless,
		R24G8_Typeless,
		R16G16B16A16_Float
	};

	enum class SamplerFilter
	{
		Nearest = 0,
		Bilinear,
		Trilinear
	};

	enum class SamplerAddressMode
	{
		Repeat = 0,
		Mirror,
		Clamp,
		Border
	};

	enum class RasterizerFillMode
	{
		Solid = 0,
		Wireframe
	};

	enum class RasterizerCullMode
	{
		None = 0,
		Front,
		Back
	};

	enum class DepthCompareFunc
	{
		Less,
		LessEqual,
		Greater,
		GreaterEqual
	};
}