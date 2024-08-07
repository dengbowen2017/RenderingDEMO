#pragma once

#include "RHI.h"
#include "RenderResource.h"
#include "RHIState.h"

namespace RenderingDEMO
{
	class RenderPass
	{
	public:
		RenderPass() = default;
		RenderPass(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> resource)
			:m_RHI(rhi), m_RenderResource(resource)
		{}
		virtual ~RenderPass() = default;
		virtual void Initialize() = 0;
		virtual void Draw() = 0;

	protected:
		std::shared_ptr<RHI> m_RHI;
		std::shared_ptr<RenderResource> m_RenderResource;
		std::shared_ptr<PipelineState> m_PiplineState;
	};
}