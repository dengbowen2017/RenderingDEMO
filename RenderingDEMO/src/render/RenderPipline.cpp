#include "RenderPipline.h"

#include "Passes/MainPass.h"

namespace RenderingDEMO
{
	void RenderPipline::Initialize(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource)
	{
		m_MainPass = std::make_shared<MainPass>(rhi, resource);
		m_MainPass->Initialize();
	}

	void RenderPipline::ForwardRendering()
	{
		m_MainPass->Draw();
	}
}