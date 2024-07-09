#include "DirectXRHIResource.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	DirectXVertexDeclaration::DirectXVertexDeclaration(const std::vector<VertexElement>& elements)
	{
		unsigned int offset = 0;
		m_Stride = 0;

		for (const auto& e : elements)
		{
			DirectXVertexElement dxElement;
			dxElement.Name = e.Name;
			dxElement.Index = e.Index;
			dxElement.Size = e.Size;
			dxElement.Offset = offset;
			switch (e.Type)
			{
			case VertexElementType::None:
				dxElement.Format = DXGI_FORMAT_UNKNOWN;
				break;
			case VertexElementType::Float:
				dxElement.Format = DXGI_FORMAT_R32_FLOAT;
				break;
			case VertexElementType::Float2:
				dxElement.Format = DXGI_FORMAT_R32G32_FLOAT;
				break;
			case VertexElementType::Float3:
				dxElement.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case VertexElementType::Float4:
				dxElement.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			case VertexElementType::UInt:
				dxElement.Format = DXGI_FORMAT_R32_UINT;
				break;
			}
			
			m_Elements.push_back(dxElement);
			offset += e.Size;
			m_Stride += e.Size;
		}
	}

	DirectXVertexShader::DirectXVertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& vs, const Microsoft::WRL::ComPtr<ID3DBlob>& blob)
		:m_VertexShader(vs), m_VertexShaderBlob(blob)
	{
	}

	DirectXPixelShader::DirectXPixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& ps)
		:m_PixelShader(ps)
	{
	}

	DirectXPipelineState::DirectXPipelineState(std::shared_ptr<DirectXVertexShader> vs, std::shared_ptr<DirectXPixelShader> ps, std::shared_ptr<DirectXVertexDeclaration> vd, std::shared_ptr<DirectXRasterizerState> rasterState, std::shared_ptr<DirectXDepthStencilState> depthState, const Microsoft::WRL::ComPtr<ID3D11Device>& device)
	{
		// set shader
		m_VertexShader = vs->GetShader();
		m_PixelShader = ps->GetShader();

		// set layout
		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutInfo;
		for (const auto& e : vd->GetElements())
		{
			layoutInfo.push_back({ e.Name.c_str(), 0, e.Format, 0, e.Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}

		if (FAILED(device->CreateInputLayout(
			layoutInfo.data(),
			static_cast<UINT>(layoutInfo.size()),
			vs->GetShaderBlob()->GetBufferPointer(),
			vs->GetShaderBlob()->GetBufferSize(),
			&m_InputLayout)))
		{
			spdlog::error("D3D11: Failed to create default vertex input layout");
			return;
		}

		m_RasterizerState = rasterState->GetState();
		m_DepthStencilState = depthState->GetState();
	}

	DirectXRasterizerState::DirectXRasterizerState(const Microsoft::WRL::ComPtr<ID3D11RasterizerState>& state)
		:m_RasterizerState(state)
	{
	}

	DirectXDepthStencilState::DirectXDepthStencilState(const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& state)
		:m_DepthStencilState(state)
	{
	}

	DirectXTexture2D::DirectXTexture2D(unsigned int width, unsigned int height, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texRes, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& srv, const Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& rtv, const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& dsv)
		:Texture2D(width, height, numMips, numSamples, flags, format), m_TextureResource(texRes), m_TextureSRV(srv), m_TextureDSV(dsv), m_TextureRTV(rtv)
	{
	}
}