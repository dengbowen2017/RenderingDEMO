#include "SkyBoxPass.h"

namespace RenderingDEMO
{
	void SkyBoxPass::Initialize()
	{
		std::vector<VertexElement> elements;
		elements.push_back({ "POSITION", 0, VertexElementType::Float3 });
		std::shared_ptr<VertexDeclaration> vd = m_RHI->CreateVertexDeclaration(elements);

		std::shared_ptr<VertexShader> vs = m_RHI->CreateVertexShader(L"skyBoxVS");
		std::shared_ptr<PixelShader> ps = m_RHI->CreatePixelShader(L"skyBoxPS");

		RasterizerStateInitializer rsInit;
		rsInit.CullMode = RasterizerCullMode::None;
		rsInit.FillMode = RasterizerFillMode::Solid;
		std::shared_ptr<RasterizerState> rasterState = m_RHI->CreateRasterizerState(rsInit);

		DepthStencilStateInitializer dsInit;
		dsInit.DepthTest = DepthCompareFunc::LessEqual;
		dsInit.EnableDepthWrite = TRUE;
		std::shared_ptr<DepthStencilState> depthState = m_RHI->CreateDepthStencilState(dsInit);

		std::shared_ptr<PipelineState> pips = m_RHI->CreatePipelineState(vs, ps, vd, rasterState, depthState);

		SamplerStateInitializer samplerInit;
		samplerInit.AddressU = SamplerAddressMode::Clamp;
		samplerInit.AddressV = SamplerAddressMode::Clamp;
		samplerInit.AddressW = SamplerAddressMode::Clamp;
		samplerInit.Filter = SamplerFilter::Nearest;
		samplerInit.MinMipLevel = 0;
		samplerInit.MaxMipLevel = 0;

		std::shared_ptr<SamplerState> Sampler = m_RHI->CreateSamplerState(samplerInit);

		m_PiplineState = pips;
		m_SamplerState = Sampler;
	}

	void SkyBoxPass::Draw()
	{
		m_RHI->SetPipelineState(m_PiplineState);

		m_RHI->SetTexture(m_RenderResource->m_SkyBoxTexture, 0);
		m_RHI->SetSamplerState(m_SamplerState, 0);

		m_RHI->SetVertexBuffer(m_RenderResource->m_SkyBoxVertexBuffer);
		m_RHI->Draw(36);

		m_RHI->SwapBuffer();
	}
}