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

	OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int id, unsigned int size)
		:m_ID(id), UniformBuffer(size)
	{
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	OpenGLTexture2D::OpenGLTexture2D(unsigned int width, unsigned int height, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, unsigned int id)
		:Texture2D(width, height, numMips, numSamples, flags, format), m_ID(id)
	{
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	OpenGLRenderTarget::OpenGLRenderTarget(std::shared_ptr<Texture2D> colorTex, std::shared_ptr<Texture2D> depthTex)
		:RenderTarget(colorTex, depthTex)
	{
		assert(colorTex != nullptr || depthTex != nullptr);
		std::shared_ptr<OpenGLTexture2D> glColorTex = std::dynamic_pointer_cast<OpenGLTexture2D>(colorTex);
		std::shared_ptr<OpenGLTexture2D> glDepthTex = std::dynamic_pointer_cast<OpenGLTexture2D>(depthTex);

		unsigned int id;
		glCreateFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);

		if (glDepthTex != nullptr && glColorTex == nullptr)
		{
			unsigned int depthMap = glDepthTex->GetID();
			glBindTexture(GL_TEXTURE_2D, depthMap);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}
		else if (glDepthTex == nullptr && glColorTex != nullptr)
		{
			unsigned int colorMap = glColorTex->GetID();
			glBindTexture(GL_TEXTURE_2D, colorMap);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorMap, 0);
		}
		else
		{
			unsigned int depthMap = glDepthTex->GetID();
			glBindTexture(GL_TEXTURE_2D, depthMap);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

			unsigned int colorMap = glColorTex->GetID();
			glBindTexture(GL_TEXTURE_2D, colorMap);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorMap, 0);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_ID = id;
	}

	OpenGLRenderTarget::~OpenGLRenderTarget()
	{
		glDeleteFramebuffers(1, &m_ID);
	}
}