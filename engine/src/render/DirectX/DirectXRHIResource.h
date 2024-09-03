#pragma once
#include "render/RenderResource.h"

//TODO: temp
#include <d3d11.h>

namespace RenderingDEMO
{
	struct DirectXVertexElement
	{
		std::string Name;
		unsigned int Index;
		DXGI_FORMAT Format;
		unsigned int Size;
		unsigned int Offset;
	};

	class DirectXVertexDeclaration : public VertexDeclaration
	{
	public:
		DirectXVertexDeclaration(const std::vector<VertexElement>& elements);
		~DirectXVertexDeclaration() = default;

		const std::vector<DirectXVertexElement>& GetElements() const { return m_Elements; }

	private:
		std::vector<DirectXVertexElement> m_Elements;
	};

	class DirectXVertexShader :public VertexShader
	{
	public:
		DirectXVertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& vs, const Microsoft::WRL::ComPtr<ID3DBlob>& blob);
		~DirectXVertexShader() = default;

		const Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetShader() const { return m_VertexShader; }
		const Microsoft::WRL::ComPtr<ID3DBlob>& GetShaderBlob() const { return m_VertexShaderBlob; }

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob> m_VertexShaderBlob;
	};

	class DirectXPixelShader :public PixelShader
	{
	public:
		DirectXPixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& ps);
		~DirectXPixelShader() = default;

		const Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetShader() const { return m_PixelShader; }

	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	};

	class DirectXVertexBuffer :public VertexBuffer
	{
	public:
		DirectXVertexBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer, unsigned int size, unsigned int stride)
			:m_Buffer(buffer), VertexBuffer(size, stride)
		{}
		~DirectXVertexBuffer() = default;

		const Microsoft::WRL::ComPtr<ID3D11Buffer>& GetBuffer() const { return m_Buffer; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};

	class DirectXIndexBuffer :public IndexBuffer
	{
	public:
		DirectXIndexBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer, unsigned int count)
			:m_Buffer(buffer), IndexBuffer(count)
		{}
		~DirectXIndexBuffer() = default;

		const Microsoft::WRL::ComPtr<ID3D11Buffer>& GetBuffer() const { return m_Buffer; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};

	class DirectXUniformBuffer :public UniformBuffer
	{
	public:
		DirectXUniformBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer, unsigned int size)
			:m_Buffer(buffer), UniformBuffer(size)
		{}
		~DirectXUniformBuffer() = default;

		const Microsoft::WRL::ComPtr<ID3D11Buffer>& GetBuffer() const { return m_Buffer; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};

	class DirectXTexture2D :public Texture2D
	{
	public:
		DirectXTexture2D(unsigned int width, unsigned int height, unsigned int arraySize, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format,
			const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texRes,
			const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& srv,
			const Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& rtv,
			const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& dsv);
		~DirectXTexture2D() = default;

		const Microsoft::WRL::ComPtr<ID3D11Texture2D>& GetTextureResource() const { return m_TextureResource; }
		const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetShaderResourceView() const { return m_TextureSRV; }
		const Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& GetRenderTargetView() const { return m_TextureRTV; }
		const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& GetDepthStencilView() const { return m_TextureDSV; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_TextureResource;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TextureSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_TextureRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_TextureDSV;
	};
}