#pragma once

#include "render/RenderPass.h"

namespace RenderingDEMO
{
	class SkyBoxPass : public RenderPass
	{
	public:
		SkyBoxPass(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource)
			:RenderPass(rhi, resource)
		{}
		~SkyBoxPass() = default;

		virtual void Initialize() override;
		virtual void Draw() override;

	private:
		std::shared_ptr<PipelineState> m_PiplineState;
		std::shared_ptr<SamplerState> m_SamplerState;
	};
}