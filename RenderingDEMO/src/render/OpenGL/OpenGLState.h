#pragma once

#include "OpenGLRHIResource.h"

namespace RenderingDEMO
{
	struct OpenGLPiplineState
	{
		unsigned int m_VAO;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		unsigned int m_ShaderProgram;
		unsigned int m_IndexCount;
		OpenGLVertexDeclaration* m_VertexDeclaration;
	};
}