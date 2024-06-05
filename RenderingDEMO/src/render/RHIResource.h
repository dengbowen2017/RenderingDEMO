#pragma once

namespace RenderingDEMO
{
	enum VertexElementType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	struct VertexElement
	{
		std::string Name;
		VertexElementType Type;
		unsigned int Size;

		VertexElement(const std::string& name, VertexElementType type)
			:Name(name), Type(type), Size(0)
		{
			switch (type)
			{
			case VertexElementType::None:
				Size = 0;
				break;
			case VertexElementType::Float:
				Size = 4;
				break;
			case VertexElementType::Float2:
				Size = 4 * 2;
				break;
			case VertexElementType::Float3:
				Size = 4 * 3;
				break;
			case VertexElementType::Float4:
				Size = 4 * 4;
				break;
			case VertexElementType::Mat3:
				Size = 4 * 3 * 3;
				break;
			case VertexElementType::Mat4:
				Size = 4 * 4 * 4;
				break;
			case VertexElementType::Int:
				Size = 4;
				break;
			case VertexElementType::Int2:
				Size = 4 * 2;
				break;
			case VertexElementType::Int3:
				Size = 4 * 3;
				break;
			case VertexElementType::Int4:
				Size = 4 * 4;
				break;
			case VertexElementType::Bool:
				Size = 1;
				break;
			}
		}
	};

	class BoundShaderState 
	{
	public:
		virtual ~BoundShaderState() = default;
	};

	class VertexShader 
	{
	public:
		virtual ~VertexShader() = default;
	};

	class PixelShader 
	{
	public:
		virtual ~PixelShader() = default;
	};

	class VertexDeclaration
	{
	public:
		virtual ~VertexDeclaration() = default;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size)
			:m_Size(size)
		{
		}
		virtual ~VertexBuffer() = default;

		unsigned int GetSize() const { return m_Size; }

	private:
		unsigned int m_Size = 0;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int count)
			:m_Count(count)
		{
		}
		virtual ~IndexBuffer() = default;

		unsigned int GetCount() const { return m_Count; }

	private:
		unsigned int m_Count = 0;
	};
}