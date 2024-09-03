#pragma once

#include "RHIDefinition.h"

namespace RenderingDEMO
{
	struct SamplerStateInitializer
	{
		SamplerFilter Filter;
		SamplerAddressMode AddressU;
		SamplerAddressMode AddressV;
		SamplerAddressMode AddressW;
		float MinMipLevel;
		float MaxMipLevel;
		float BorderColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct RasterizerStateInitializer
	{
		RasterizerCullMode CullMode;
		RasterizerFillMode FillMode;
	};

	struct DepthStencilStateInitializer
	{
		bool EnableDepthWrite;
		DepthCompareFunc DepthTest;
	};

	class SamplerState
	{
	public:
		virtual ~SamplerState() = default;
	};

	class RasterizerState
	{
	public:
		virtual ~RasterizerState() = default;
	};

	class DepthStencilState
	{
	public:
		virtual ~DepthStencilState() = default;
	};

	class PipelineState
	{
	public:
		virtual ~PipelineState() = default;
	};
}