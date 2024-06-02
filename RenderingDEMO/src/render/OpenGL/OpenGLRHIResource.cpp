#include "OpenGLRHIResource.h"
#include "glad/glad.h"

namespace RenderingDEMO
{
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}
}