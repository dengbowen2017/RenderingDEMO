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

		virtual void CreateSwapChain() = 0;
		virtual void RecreateSwapChain() = 0;

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(void* data, unsigned int size) = 0;
		virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(void* data, unsigned int size) = 0;
		virtual std::shared_ptr<VertexDeclaration> CreateVertexDeclaration(const std::vector<VertexElement>& elements) = 0;
		virtual void CreateShaderState() = 0;

		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> ib) = 0;
		virtual void SetShaderState(std::shared_ptr<VertexDeclaration> vd) = 0;

		virtual void ClearBackBuffer(float r, float g, float b, float a) = 0;
		virtual void SwapBuffer() = 0;
		virtual void Draw(unsigned int count) = 0;
	};
}