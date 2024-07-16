#include "RenderPipline.h"

#include "Passes/MainPass.h"
#include "Passes/ShadowPass.h"

namespace RenderingDEMO
{
	void RenderPipline::Initialize(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource)
	{
		std::shared_ptr<ShadowPass> shadowPass = std::make_shared<ShadowPass>(rhi, resource);
		shadowPass->Initialize();

		std::shared_ptr<MainPass> mainPass = std::make_shared<MainPass>(rhi, resource);
		mainPass->Initialize();

		mainPass->m_DepthMap = shadowPass->m_RenderTarget->GetDepthStencilTexture();

		m_MainPass = mainPass;
		m_ShadowPass = shadowPass;
	}

	void RenderPipline::ForwardRendering()
	{
		m_ShadowPass->Draw();
		m_MainPass->Draw();
	}
}