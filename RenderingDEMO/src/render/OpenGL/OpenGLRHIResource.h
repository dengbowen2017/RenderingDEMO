#pragma once

#include "render/RHIResource.h"

namespace RenderingDEMO
{
	struct OpenGLVertexElement
	{
		std::string Name;
		unsigned int Index;
		unsigned int Type;
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

	class OpenGLPipelineState :public PipelineState
	{
	public:
		OpenGLPipelineState(std::shared_ptr<OpenGLVertexShader> vs, std::shared_ptr<OpenGLPixelShader> ps, std::shared_ptr<OpenGLVertexDeclaration> vd);
		~OpenGLPipelineState();

	public:
		unsigned int m_ID;
		std::shared_ptr<OpenGLVertexDeclaration> m_VertexDeclaration;
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
}