#pragma once

#include "RHI.h"
#include "RHIResource.h"
#include "RenderDefinition.h"

namespace RenderingDEMO
{
	class RenderResource
	{
	public:
		RenderResource() = default;
		~RenderResource() = default;


	public:
		// temp 
		// need Mesh and Object class to manage all the buffers
		std::shared_ptr<VertexBuffer> m_CubeVertexBuffer;
		std::shared_ptr<IndexBuffer> m_CubeIndexBuffer;
		std::shared_ptr<UniformBuffer> m_PerFrameUniformBuffer;
		std::shared_ptr<UniformBuffer> m_PerObjectUniformBuffer;

		std::shared_ptr<PipelineState> m_PipelineState;

		PerFrameConstant m_PerFrameConstant;
		PerObjectConstant m_PerObjectConstant;
	};
}