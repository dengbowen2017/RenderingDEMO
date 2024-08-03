#pragma once

#include "RenderPass.h"

namespace RenderingDEMO
{
	class WindowUI;

	class RenderPipline
	{
	public:
		void Initialize(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource);
		void InitializeUI(std::shared_ptr<WindowUI> ui);
		void ForwardRendering();

	private:
		std::shared_ptr<RenderPass> m_ShadowPass;
		std::shared_ptr<RenderPass> m_MainPass;
		std::shared_ptr<RenderPass> m_UIPass;
	};

}