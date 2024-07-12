#pragma once

#include "RHIDefinition.h"

namespace RenderingDEMO
{
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

	class Texture
	{
	public:
		Texture(unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format)
			:m_NumMips(numMips), m_NumSamples(numSamples), m_Flags(flags), m_Format(format)
		{}
		virtual ~Texture() = default;

	private:
		unsigned int m_NumMips;
		unsigned int m_NumSamples;
		unsigned int m_Flags;
		TextureFormat m_Format;
	};

	class Texture2D :public Texture
	{
	public:
		Texture2D(unsigned int width, unsigned int height, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format)
			:m_Width(width), m_Height(height), Texture(numMips, numSamples, flags, format)
		{}
		virtual ~Texture2D() = default;

		std::array<unsigned int, 2> GetTexSize() const { return std::array<unsigned int, 2>({ m_Width, m_Height }); }

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class RenderTarget
	{
	public:
		RenderTarget(std::shared_ptr<Texture2D> rtvTex, std::shared_ptr<Texture2D> dsvTex)
		{}
		virtual ~RenderTarget() = default;

		std::shared_ptr<Texture2D> GetRenderTargetTexture() const { return m_RenderTargetTexture; }
		std::shared_ptr<Texture2D> GetDepthStencilTexture() const { return m_DepthStencilTexture; }

	protected:
		std::shared_ptr<Texture2D> m_RenderTargetTexture;
		std::shared_ptr<Texture2D> m_DepthStencilTexture;
	};
}