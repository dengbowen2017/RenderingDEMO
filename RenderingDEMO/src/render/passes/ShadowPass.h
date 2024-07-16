#pragma once

#include "render/RenderPass.h"

namespace RenderingDEMO
{
	class ShadowPass :public RenderPass
	{
	public:
		ShadowPass(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource)
			:RenderPass(rhi, resource)
		{}
		~ShadowPass() = default;

		virtual void Initialize() override;
		virtual void Draw() override;

	public:
		std::shared_ptr<RenderTarget> m_RenderTarget;

		// temp
		unsigned int m_ShadowMapWidth = 2048;
		unsigned int m_ShadowMapHeight = 2048;
	};
}