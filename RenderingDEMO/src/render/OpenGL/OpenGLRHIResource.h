#pragma once

#include "render/RHIResource.h"
#include <glad/glad.h>

namespace RenderingDEMO
{
	struct OpenGLVertexElement
	{
		std::string Name;
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

	public:
		std::vector<OpenGLVertexElement> m_Elements;
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

}