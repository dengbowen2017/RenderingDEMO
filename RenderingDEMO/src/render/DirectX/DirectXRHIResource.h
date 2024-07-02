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

	class DirectXRasterizerState :public RasterizerState
	{
	public:
		DirectXRasterizerState(const Microsoft::WRL::ComPtr<ID3D11RasterizerState>& state);
		~DirectXRasterizerState() = default;

		const Microsoft::WRL::ComPtr<ID3D11RasterizerState>& GetState() const { return m_RasterizerState; }

	private:
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RasterizerState;
	};

	class DirectXDepthStencilState :public DepthStencilState
	{
	public:
		DirectXDepthStencilState(const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& state);
		~DirectXDepthStencilState() = default;

		const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& GetState() const { return m_DepthStencilState; }

	private:
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
	};

	class DirectXPipelineState :public PipelineState
	{
	public:
		DirectXPipelineState(std::shared_ptr<DirectXVertexShader> vs, std::shared_ptr<DirectXPixelShader> ps, std::shared_ptr<DirectXVertexDeclaration> vd, 
			std::shared_ptr<DirectXRasterizerState> rasterState, std::shared_ptr<DirectXDepthStencilState> depthState, const Microsoft::WRL::ComPtr<ID3D11Device>& device);
		~DirectXPipelineState() = default;

	public:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RasterizerState;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
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
}