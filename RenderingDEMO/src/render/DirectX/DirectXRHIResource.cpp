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

	DirectXTexture2D::DirectXTexture2D(unsigned int width, unsigned int height, unsigned int arraySize, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texRes, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& srv, const Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& rtv, const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& dsv)
		:Texture2D(width, height, arraySize, numMips, numSamples, flags, format), m_TextureResource(texRes), m_TextureSRV(srv), m_TextureDSV(dsv), m_TextureRTV(rtv)
	{
	}
}