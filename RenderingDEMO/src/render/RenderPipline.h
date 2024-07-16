#pragma once

#include "RenderPass.h"

namespace RenderingDEMO
{
	class RenderPipline
	{
	public:
		void Initialize(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource);
		void ForwardRendering();

	private:
		std::shared_ptr<RenderPass> m_ShadowPass;
		std::shared_ptr<RenderPass> m_MainPass;
		std::shared_ptr<RenderPass> m_UIPass;
	};

}