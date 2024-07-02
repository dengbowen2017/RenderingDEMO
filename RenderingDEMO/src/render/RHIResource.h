#pragma once

namespace RenderingDEMO
{
	enum VertexElementType
	{
		None = 0, Float, Float2, Float3, Float4, UInt
	};

	struct VertexElement
	{
		std::string Name;
		VertexElementType Type;
		unsigned int Size;
		unsigned int Index;			//different meaning in OpenGL and DirectX

		VertexElement(const std::string& name, unsigned int index, VertexElementType type)
			:Name(name), Type(type), Size(0), Index(index)
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
			case VertexElementType::UInt:
				Size = 4;
				break;
			}
		}
	};

	class VertexDeclaration
	{
	public:
		virtual ~VertexDeclaration() = default;

		unsigned int GetStride() const { return m_Stride; }
	
	protected:
		unsigned int m_Stride;
	};

	class RasterizerState
	{
	public:
		virtual ~RasterizerState() = default;
	};

	class DepthStencilState
	{
	public:
		virtual ~DepthStencilState() = default;
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

	class PipelineState
	{
	public:
		virtual ~PipelineState() = default;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size, unsigned int stride)
			:m_Size(size), m_Stride(stride)
		{
		}
		virtual ~VertexBuffer() = default;

		unsigned int GetSize() const { return m_Size; }
		unsigned int GetStride() const { return m_Stride; }

	private:
		unsigned int m_Size = 0;
		unsigned int m_Stride = 0;
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

	class UniformBuffer
	{
	public:
		UniformBuffer(unsigned int size)
			:m_Size(size)
		{
		}
		virtual ~UniformBuffer() = default;

		unsigned int GetSize() const { return m_Size; }

	private:
		unsigned int m_Size = 0;
	};
}