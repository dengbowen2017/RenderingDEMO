#pragma once

#include "render/RHIResource.h"

namespace RenderingDEMO
{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size, unsigned int id)
			:VertexBuffer(size), m_ID(id)
		{
		}

		~OpenGLVertexBuffer();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
	};

}