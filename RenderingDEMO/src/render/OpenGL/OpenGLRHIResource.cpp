#include "OpenGLRHIResource.h"
#include "glad/glad.h"

namespace RenderingDEMO
{
	OpenGLVertexDeclaration::OpenGLVertexDeclaration(const std::vector<VertexElement>& elements)
	{
		unsigned int offset = 0;
		m_Stride = 0;
		for (const auto& e : elements)
		{
			OpenGLVertexElement glElement;
			glElement.Name = e.Name;
			glElement.Size = e.Size;
			
			switch (e.Type)
			{
			case VertexElementType::None:
				glElement.Type = GL_NONE;
				glElement.Count = 0;
				glElement.Offset = offset;
				break;
			case VertexElementType::Float:
				glElement.Type = GL_FLOAT;
				glElement.Count = 1;
				glElement.Offset = offset;
				break;
			case VertexElementType::Float2:
				glElement.Type = GL_FLOAT;
				glElement.Count = 2;
				glElement.Offset = offset;
				break;
			case VertexElementType::Float3:
				glElement.Type = GL_FLOAT;
				glElement.Count = 3;
				glElement.Offset = offset;
				break;
			case VertexElementType::Float4:
				glElement.Type = GL_FLOAT;
				glElement.Count = 4;
				glElement.Offset = offset;
				break;
			case VertexElementType::Mat3:
				glElement.Type = GL_FLOAT;
				glElement.Count = 3 * 3;
				glElement.Offset = offset;
				break;
			case VertexElementType::Mat4:
				glElement.Type = GL_FLOAT;
				glElement.Count = 4 * 4;
				glElement.Offset = offset;
				break;
			case VertexElementType::Int:
				glElement.Type = GL_INT;
				glElement.Count = 1;
				glElement.Offset = offset;
				break;
			case VertexElementType::Int2:
				glElement.Type = GL_INT;
				glElement.Count = 2;
				glElement.Offset = offset;
				break;
			case VertexElementType::Int3:
				glElement.Type = GL_INT;
				glElement.Count = 3;
				glElement.Offset = offset;
				break;
			case VertexElementType::Int4:
				glElement.Type = GL_INT;
				glElement.Count = 4;
				glElement.Offset = offset;
				break;
			case VertexElementType::Bool:
				glElement.Type = GL_BOOL;
				glElement.Count = 1;
				glElement.Offset = offset;
				break;
			}

			m_Elements.push_back(glElement);
			offset += e.Size;
			m_Stride += e.Size;
		}
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size, unsigned int id)
		:VertexBuffer(size), m_ID(id)
	{
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int count, unsigned int id)
		:IndexBuffer(count), m_ID(id)
	{
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}
}