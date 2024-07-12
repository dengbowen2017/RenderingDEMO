#pragma once

#include "RHI.h"
#include "RHIResource.h"
#include "RenderDefinition.h"
#include "Camera.h"

namespace RenderingDEMO
{
	class RenderResource
	{
	public:
		void UpdatePerFrameConstant(std::shared_ptr<Camera> camera);
		void UpdateBuffers(std::shared_ptr<RHI> rhi);

	public:
		// temp 
		// need Mesh and Object class to manage all the buffers
		std::shared_ptr<VertexDeclaration> m_VertexDeclaration;
		std::shared_ptr<VertexBuffer> m_CubeVertexBuffer;
		std::shared_ptr<IndexBuffer> m_CubeIndexBuffer;

		std::shared_ptr<UniformBuffer> m_PerFrameUniformBuffer;
		std::shared_ptr<UniformBuffer> m_PerObjectUniformBuffer;

		PerFrameConstant m_PerFrameConstant;

		std::shared_ptr<PipelineState> m_PipelineState;
	};
}