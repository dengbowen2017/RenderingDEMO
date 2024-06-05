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
		unsigned int GetStride() const { return m_Stride; }

	private:
		std::vector<OpenGLVertexElement> m_Elements;
		unsigned int m_Stride = 0;
	};

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size, unsigned int id);
		~OpenGLVertexBuffer();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID = 0;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int count, unsigned int id);
		~OpenGLIndexBuffer();

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
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

	class OpenGLBoundShaderState :public BoundShaderState
	{
	public:
		OpenGLBoundShaderState(std::shared_ptr<OpenGLVertexShader> vs, std::shared_ptr<OpenGLPixelShader> ps, std::shared_ptr<OpenGLVertexDeclaration> vd);
		~OpenGLBoundShaderState();

		unsigned int GetID() const { return m_ID; }
		std::shared_ptr<OpenGLVertexDeclaration> GetVertexDeclaration() const { return m_VertexDeclaration; }

	private:
		unsigned int m_ID;
		std::shared_ptr<OpenGLVertexDeclaration> m_VertexDeclaration;
	};
}