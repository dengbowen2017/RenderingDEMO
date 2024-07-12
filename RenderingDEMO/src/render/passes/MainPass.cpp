#include "MainPass.h"

namespace RenderingDEMO
{
	void MainPass::Initialize()
	{
		std::shared_ptr<VertexDeclaration> vd = m_RenderResource->m_VertexDeclaration;
		assert(vd != nullptr);

		std::shared_ptr<VertexShader> vs = m_RHI->CreateVertexShader(L"../shader/vs" );
		std::shared_ptr<PixelShader> ps = m_RHI->CreatePixelShader(L"../shader/ps");

		RasterizerStateInitializer rsInit;
		rsInit.CullMode = RasterizerCullMode::Back;
		rsInit.FillMode = RasterizerFillMode::Solid;

		std::shared_ptr<RasterizerState> rasterState = m_RHI->CreateRasterizerState(rsInit);

		DepthStencilStateInitializer dsInit;
		dsInit.DepthTest = DepthCompareFunc::Less;
		dsInit.EnableDepthWrite = TRUE;

		std::shared_ptr<DepthStencilState> depthState = m_RHI->CreateDepthStencilState(dsInit);

		// move to pass
		std::shared_ptr<PipelineState> pips = m_RHI->CreatePipelineState(vs, ps, vd, rasterState, depthState);

		m_PiplineState = pips;
	}

	void MainPass::Draw()
	{
		m_RHI->ClearBackBuffer();
		// shadow pass


		// main pass
		m_RHI->SetPipelineState(m_PiplineState);
		m_RHI->SetVertexBuffer(m_RenderResource->m_CubeVertexBuffer);
		m_RHI->SetRenderTarget(nullptr);
		m_RHI->Draw(36);

		m_RHI->SwapBuffer();
	}
}