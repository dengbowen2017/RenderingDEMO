#include "DirectXRHIState.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
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

		m_RasterizerState = rasterState->m_RasterizerState;
		m_DepthStencilState = depthState->m_DepthStencilState;
	}
}