#pragma once

#include "render/RenderPass.h"
#include "render/RHIState.h"
#include "ShadowPass.h"

namespace RenderingDEMO
{
	class MainPass :public RenderPass
	{
	public:
		MainPass(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource)
			:RenderPass(rhi, resource)
		{}
		~MainPass() = default;

		virtual void Initialize() override;
		virtual void Draw() override;

	private:
		std::shared_ptr<ShadowPass> m_ShadowPass;
	};
}