#pragma once

#include "RHI.h"
#include "RHIResource.h"

namespace RenderingDEMO
{
	class RenderResource
	{
	public:
		RenderResource() = default;
		~RenderResource() = default;

	// temp 
	// need Mesh and Object class to manage all the buffers
	public:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::vector<std::shared_ptr<IndexBuffer>> m_IndexBuffers;
		
		std::unordered_map<std::string, std::shared_ptr<VertexDeclaration>> m_VertexDeclarations;
		std::unordered_map<std::string, std::shared_ptr<VertexShader>> m_VertexShaders;
		std::unordered_map<std::string, std::shared_ptr<PixelShader>> m_PixelShaders;

		std::shared_ptr<PipelineState> m_PipelineState;
		std::shared_ptr<UniformBuffer> m_UniformBuffer;
	};
}