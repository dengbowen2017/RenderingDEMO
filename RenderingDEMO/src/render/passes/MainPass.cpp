#include "MainPass.h"

namespace RenderingDEMO
{
	void MainPass::Initialize()
	{
		std::vector<VertexElement> elements;
		elements.push_back({ "POSITION", 0, VertexElementType::Float3 });
		elements.push_back({ "NORMAL", 0, VertexElementType::Float3 });
		elements.push_back({ "TEXCOORD", 0, VertexElementType::Float2 });
		std::shared_ptr<VertexDeclaration> vd = m_RHI->CreateVertexDeclaration(elements);

		std::shared_ptr<VertexShader> vs = m_RHI->CreateVertexShader(L"mainVS" );
		std::shared_ptr<PixelShader> ps = m_RHI->CreatePixelShader(L"mainPS");

		RasterizerStateInitializer rsInit;
		rsInit.CullMode = RasterizerCullMode::Back;
		rsInit.FillMode = RasterizerFillMode::Solid;
		std::shared_ptr<RasterizerState> rasterState = m_RHI->CreateRasterizerState(rsInit);

		DepthStencilStateInitializer dsInit;
		dsInit.DepthTest = DepthCompareFunc::Less;
		dsInit.EnableDepthWrite = TRUE;
		std::shared_ptr<DepthStencilState> depthState = m_RHI->CreateDepthStencilState(dsInit);

		std::shared_ptr<PipelineState> pips = m_RHI->CreatePipelineState(vs, ps, vd, rasterState, depthState);

		SamplerStateInitializer samplerInit;
		samplerInit.AddressU = SamplerAddressMode::Border;
		samplerInit.AddressV = SamplerAddressMode::Border;
		samplerInit.AddressW = SamplerAddressMode::Repeat;
		samplerInit.Filter = SamplerFilter::Nearest;
		samplerInit.MinMipLevel = 0;
		samplerInit.MaxMipLevel = 0; 

		std::shared_ptr<SamplerState> depthSampler = m_RHI->CreateSamplerState(samplerInit);

		samplerInit.AddressU = SamplerAddressMode::Repeat;
		samplerInit.AddressV = SamplerAddressMode::Repeat;
		std::shared_ptr<SamplerState> diffuseSampler = m_RHI->CreateSamplerState(samplerInit);

		m_PiplineState = pips;
		m_DepthSamplerState = depthSampler;
		m_DiffuseSamplerState = diffuseSampler;
	}

	void MainPass::Draw()
	{
		m_RHI->SetRenderTarget(nullptr);
		m_RHI->ClearRenderTarget(nullptr);

		m_RHI->SetViewPort(0, 0); // set to window size

		m_RHI->SetPipelineState(m_PiplineState);

		m_RHI->SetTexture(m_DepthMap, 0);
		m_RHI->SetSamplerState(m_DepthSamplerState, 0);

		m_RHI->SetTexture(m_RenderResource->m_BoxTexture, 1);
		m_RHI->SetSamplerState(m_DiffuseSamplerState, 1);

		m_RHI->SetVertexBuffer(m_RenderResource->m_CubeVertexBuffer);
		m_RHI->Draw(36);

		m_RHI->SetTexture(m_RenderResource->m_WallTexture, 1);
		m_RHI->SetSamplerState(m_DiffuseSamplerState, 1);

		m_RHI->SetVertexBuffer(m_RenderResource->m_PlaneVertexBuffer);
		m_RHI->DrawIndexed(m_RenderResource->m_PlaneIndexBuffer);

		//m_RHI->SetVertexBuffer(m_RenderResource->m_QuadVertexBuffer);
		//m_RHI->DrawIndexed(m_RenderResource->m_QuadIndexBuffer);

		//m_RHI->SwapBuffer();
	}
}