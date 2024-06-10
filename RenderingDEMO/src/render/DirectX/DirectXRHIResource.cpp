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

	DirectXBoundShaderState::DirectXBoundShaderState(std::shared_ptr<DirectXVertexShader> vs, std::shared_ptr<DirectXPixelShader> ps, std::shared_ptr<DirectXVertexDeclaration> vd, const Microsoft::WRL::ComPtr<ID3D11Device>& device)
	{
		m_VertexShader = vs->GetShader();
		m_PixelShader = ps->GetShader();
		m_Stride = vd->GetStride();
		
		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutInfo;
		for (const auto& e : vd->GetElements())
		{
			layoutInfo.push_back({ e.Name.c_str(), 0, e.Format, 0, e.Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}

		if (FAILED(device->CreateInputLayout(
			layoutInfo.data(),
			layoutInfo.size(),
			vs->GetShaderBlob()->GetBufferPointer(),
			vs->GetShaderBlob()->GetBufferSize(),
			&m_InputLayout)))
		{
			spdlog::error("D3D11: Failed to create default vertex input layout");
			return;
		}
	}
}