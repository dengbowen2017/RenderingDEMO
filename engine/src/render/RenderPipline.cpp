#include "RenderPipline.h"

#include "Passes/MainPass.h"
#include "Passes/ShadowPass.h"
#include "Passes/UIPass.h"
#include "Passes/SkyBoxPass.h"

namespace RenderingDEMO
{
	void RenderPipline::Initialize(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource)
	{
		std::shared_ptr<ShadowPass> shadowPass = std::make_shared<ShadowPass>(rhi, resource);
		shadowPass->Initialize();

		std::shared_ptr<MainPass> mainPass = std::make_shared<MainPass>(rhi, resource);
		mainPass->Initialize();
		mainPass->m_DepthMap = shadowPass->m_RenderTarget->GetDepthStencilTexture();

		std::shared_ptr<SkyBoxPass> skyBoxPass = std::make_shared<SkyBoxPass>(rhi, resource);
		skyBoxPass->Initialize();

		m_MainPass = mainPass;
		m_ShadowPass = shadowPass;
		m_SkyBoxPass = skyBoxPass;
	}

	void RenderPipline::InitializeUI(std::shared_ptr<WindowUI> ui)
	{
		std::shared_ptr<UIPass> uiPass = std::make_shared<UIPass>(ui);
		m_UIPass = uiPass;
	}

	void RenderPipline::ForwardRendering()
	{
		m_ShadowPass->Draw();
		m_MainPass->Draw();
		//m_UIPass->Draw();
		m_SkyBoxPass->Draw();
	}
}