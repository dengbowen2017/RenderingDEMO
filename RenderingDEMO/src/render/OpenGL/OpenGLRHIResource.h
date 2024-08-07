#pragma once

#include "render/RHIResource.h"
#include "render/RHIState.h"

#include <glad/glad.h>

namespace RenderingDEMO
{
	struct OpenGLVertexElement
	{
		std::string Name;
		unsigned int Index;
		GLenum Type;
		unsigned int Size;
		unsigned int Offset;
		unsigned int Count;
	};

	class OpenGLVertexDeclaration :public VertexDeclaration
	{
	public:
		OpenGLVertexDeclaration(const std::vector<VertexElement>& elements);
		~OpenGLVertexDeclaration() = default;

		const std::vector<OpenGLVertexElement>& GetElements() const { return m_Elements; }

	private:
		std::vector<OpenGLVertexElement> m_Elements;
	};

	class OpenGLVertexShader :public VertexShader
	{
	public:
		OpenGLVertexShader(unsigned int id);
		~OpenGLVertexShader();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
	};

	class OpenGLPixelShader :public PixelShader
	{
	public:
		OpenGLPixelShader(unsigned int id);
		~OpenGLPixelShader();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
	};

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int id, unsigned int size, unsigned int stride);
		~OpenGLVertexBuffer();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID = 0;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int id, unsigned int count);
		~OpenGLIndexBuffer();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
	};

	class OpenGLUniformBuffer :public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(unsigned int id, unsigned int size);
		~OpenGLUniformBuffer();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
	};

	class OpenGLTexture2D :public Texture2D
	{
	public:
		OpenGLTexture2D(unsigned int width, unsigned int height, unsigned int arraySize, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, unsigned int id);
		~OpenGLTexture2D();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
	};

	class OpenGLRenderTarget :public RenderTarget
	{
	public:
		OpenGLRenderTarget(std::shared_ptr<Texture2D> colorTex, std::shared_ptr<Texture2D> depthTex);
		~OpenGLRenderTarget();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
	};
}