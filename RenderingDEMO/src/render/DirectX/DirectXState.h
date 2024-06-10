#pragma once

#include "d3d11.h"
#include "dxgi1_3.h"

namespace RenderingDEMO
{
	struct DirectXState
	{
		ID3D11Buffer* m_VertexBuffer;
		ID3D11Buffer* m_IndexBuffer;
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;
		ID3D11InputLayout* m_InputLayout;
		unsigned int m_VertexStride;
		unsigned int m_IndexCount;
	};
}