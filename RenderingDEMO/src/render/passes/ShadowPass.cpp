#include "ShadowPass.h"

namespace RenderingDEMO
{
	void ShadowPass::Initialize()
	{
		std::vector<VertexElement> elements;
		elements.push_back({ "POSITION", 0, VertexElementType::Float3 });
		elements.push_back({ "NORMAL", 0, VertexElementType::Float3 });
		elements.push_back({ "TEXCOORD", 0, VertexElementType::Float2 });
		std::shared_ptr<VertexDeclaration> vd = m_RHI->CreateVertexDeclaration(elements);

		std::shared_ptr<VertexShader> vs = m_RHI->CreateVertexShader(L"shadowVS");
		std::shared_ptr<PixelShader> ps = m_RHI->CreatePixelShader(L"shadowPS");

		RasterizerStateInitializer rsInit;
		rsInit.CullMode = RasterizerCullMode::Back;
		rsInit.FillMode = RasterizerFillMode::Solid;
		std::shared_ptr<RasterizerState> rasterState = m_RHI->CreateRasterizerState(rsInit);

		DepthStencilStateInitializer dsInit;
		dsInit.DepthTest = DepthCompareFunc::Less;
		dsInit.EnableDepthWrite = TRUE;
		std::shared_ptr<DepthStencilState> depthState = m_RHI->CreateDepthStencilState(dsInit);

		std::shared_ptr<PipelineState> pips = m_RHI->CreatePipelineState(vs, ps, vd, rasterState, depthState);

		m_PiplineState = pips;

		unsigned int flags = (unsigned int)TextureFlags::TexDepthStencilTarget | (unsigned int)TextureFlags::TexShaderResource | (unsigned int)TextureFlags::TexDefault;
		ResourceRawData raw_data;
		std::shared_ptr<Texture2D> depthTex = m_RHI->CreateTexture2D(m_ShadowMapWidth, m_ShadowMapHeight, 1, 1, 1, flags, TextureFormat::R32_Typeless, raw_data);

		m_RenderTarget = m_RHI->CreateRenderTarget(nullptr, depthTex);
	}

	void ShadowPass::Draw()
	{
		m_RHI->SetRenderTarget(m_RenderTarget);
		m_RHI->ClearRenderTarget(m_RenderTarget);

		m_RHI->SetPipelineState(m_PiplineState);
		m_RHI->SetViewPort(static_cast<float>(m_ShadowMapWidth), static_cast<float>(m_ShadowMapHeight));

		m_RHI->SetVertexBuffer(m_RenderResource->m_CubeVertexBuffer);
		m_RHI->Draw(36);

		m_RHI->SetVertexBuffer(m_RenderResource->m_PlaneVertexBuffer);
		m_RHI->DrawIndexed(m_RenderResource->m_PlaneIndexBuffer);
	}
}