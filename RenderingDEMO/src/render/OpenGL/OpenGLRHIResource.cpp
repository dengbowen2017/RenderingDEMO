#include "OpenGLRHIResource.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	OpenGLVertexDeclaration::OpenGLVertexDeclaration(const std::vector<VertexElement>& elements)
	{
		unsigned int offset = 0;
		unsigned int index = 0;
		m_Stride = 0;

		for (const auto& e : elements)
		{
			OpenGLVertexElement glElement;
			glElement.Name = e.Name;
			glElement.Index = index;
			glElement.Size = e.Size;
			glElement.Offset = offset;

			switch (e.Type)
			{
			case VertexElementType::None:
				glElement.Type = GL_NONE;
				glElement.Count = 0;
				break;
			case VertexElementType::Float:
				glElement.Type = GL_FLOAT;
				glElement.Count = 1;
				break;
			case VertexElementType::Float2:
				glElement.Type = GL_FLOAT;
				glElement.Count = 2;
				break;
			case VertexElementType::Float3:
				glElement.Type = GL_FLOAT;
				glElement.Count = 3;
				break;
			case VertexElementType::Float4:
				glElement.Type = GL_FLOAT;
				glElement.Count = 4;
				break;
			case VertexElementType::UInt:
				glElement.Type = GL_UNSIGNED_INT;
				glElement.Count = 1;
				break;
			}

			m_Elements.push_back(glElement);
			offset += e.Size;
			index ++;
			m_Stride += e.Size;
		}
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int id, unsigned int size, unsigned int stride)
		:VertexBuffer(size, stride), m_ID(id)
	{
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int id, unsigned int count)
		:IndexBuffer(count), m_ID(id)
	{
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	OpenGLVertexShader::OpenGLVertexShader(unsigned int id)
		:m_ID(id)
	{
	}

	OpenGLVertexShader::~OpenGLVertexShader()
	{
		glDeleteShader(m_ID);
	}

	OpenGLPixelShader::OpenGLPixelShader(unsigned int id)
		:m_ID(id)
	{
	}

	OpenGLPixelShader::~OpenGLPixelShader()
	{
		glDeleteShader(m_ID);
	}

	OpenGLPipelineState::OpenGLPipelineState(std::shared_ptr<OpenGLVertexShader> vs, std::shared_ptr<OpenGLPixelShader> ps, std::shared_ptr<OpenGLVertexDeclaration> vd)
	{
		m_VertexDeclaration = vd;

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
			spdlog::error("OpenGL Shader Program Linking Failed:", infoLog);
		}
	}

	OpenGLPipelineState::~OpenGLPipelineState()
	{
		glDeleteProgram(m_ID);
	}

	OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int id, unsigned int size)
		:m_ID(id), UniformBuffer(size)
	{
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}
}