#pragma once

#include "render/RHIState.h"
#include "DirectXRHIResource.h"

namespace RenderingDEMO
{
	class DirectXSamplerState :public SamplerState
	{
	public:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SamplerState;
	};

	class DirectXRasterizerState :public RasterizerState
	{
	public:
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RasterizerState;
	};

	class DirectXDepthStencilState :public DepthStencilState
	{
	public:
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
	};

	class DirectXPipelineState :public PipelineState
	{
	public:
		DirectXPipelineState(std::shared_ptr<DirectXVertexShader> vs, std::shared_ptr<DirectXPixelShader> ps, std::shared_ptr<DirectXVertexDeclaration> vd,
			std::shared_ptr<DirectXRasterizerState> rasterState, std::shared_ptr<DirectXDepthStencilState> depthState, const Microsoft::WRL::ComPtr<ID3D11Device>& device);

	public:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RasterizerState;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
	};
}