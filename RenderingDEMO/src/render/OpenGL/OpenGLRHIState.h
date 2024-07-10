#pragma once

#include "OpenGLRHIResource.h"

namespace RenderingDEMO
{
	class OpenGLSamplerState :public SamplerState
	{
	public:
		unsigned int m_ID;
	};

	class OpenGLRasterizerState :public RasterizerState
	{
	public:
		GLenum m_CullMode;
		GLenum m_FillMode;
	};

	class OpenGLDepthStencilState :public DepthStencilState
	{
	public:
		GLenum m_DepthFunc;
		GLboolean m_DepthMask;
	};

	class OpenGLPipelineState :public PipelineState
	{
	public:
		OpenGLPipelineState(std::shared_ptr<OpenGLVertexShader> vs, std::shared_ptr<OpenGLPixelShader> ps, std::shared_ptr<OpenGLVertexDeclaration> vd,
			std::shared_ptr<OpenGLRasterizerState> rasterState, std::shared_ptr<OpenGLDepthStencilState> depthState);
		~OpenGLPipelineState();

	public:
		unsigned int m_ID;
		std::shared_ptr<OpenGLVertexDeclaration> m_VertexDeclaration;
		std::shared_ptr<OpenGLRasterizerState> m_RasterizerState;
		std::shared_ptr<OpenGLDepthStencilState> m_DepthStencilState;
	};
}