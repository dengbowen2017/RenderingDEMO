#pragma once

#include "render/RenderPass.h"

namespace RenderingDEMO
{
	class UIPass :public RenderPass
	{
	public:
		UIPass(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource)
			:RenderPass(rhi, resource)
		{}
		~UIPass() = default;

		virtual void Initialize() override;
		virtual void Draw() override;

	private:
		std::shared_ptr<RenderTarget> m_RenderTarget;
	};
}