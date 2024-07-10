#include "OpenGLRHIState.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	OpenGLPipelineState::OpenGLPipelineState(std::shared_ptr<OpenGLVertexShader> vs, std::shared_ptr<OpenGLPixelShader> ps, std::shared_ptr<OpenGLVertexDeclaration> vd, std::shared_ptr<OpenGLRasterizerState> rasterState, std::shared_ptr<OpenGLDepthStencilState> depthState)
	{
		m_VertexDeclaration = vd;
		m_RasterizerState = rasterState;
		m_DepthStencilState = depthState;

		int success = 0;
		char infoLog[512];
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vs->GetID());
		glAttachShader(m_ID, ps->GetID());
		glLinkProgram(m_ID);

		// check for linking errors
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
			spdlog::error("OpenGL Shader Program Linking Failed:{0}", infoLog);
		}
	}

	OpenGLPipelineState::~OpenGLPipelineState()
	{
		glDeleteProgram(m_ID);
	}
}