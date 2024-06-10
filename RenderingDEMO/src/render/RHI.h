#pragma once

#include "core/Window.h"
#include "RHIResource.h"

namespace RenderingDEMO
{
	class RHI
	{
	public:
		virtual ~RHI() = default;

		virtual void Initialize(std::shared_ptr<Window> window) = 0;

		virtual void RecreateSwapChain(int width, int height) = 0;

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(void* data, unsigned int size) = 0;
		virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(void* data, unsigned int size) = 0;
		virtual std::shared_ptr<VertexDeclaration> CreateVertexDeclaration(const std::vector<VertexElement>& elements) = 0;
		virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::wstring& filePath) = 0;
		virtual std::shared_ptr<PixelShader> CreatePixelShader(const std::wstring& filePath) = 0;
		virtual std::shared_ptr<BoundShaderState> CreateBoundShaderState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd) = 0;

		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> ib) = 0;
		virtual void SetVertexLayout(std::shared_ptr<VertexDeclaration> vd) = 0;
		virtual void SetBoundShaderState(std::shared_ptr<BoundShaderState> state) = 0;

		virtual void ClearBackBuffer() = 0;
		virtual void SwapBuffer() = 0;
		virtual void Draw() = 0;
	};
}