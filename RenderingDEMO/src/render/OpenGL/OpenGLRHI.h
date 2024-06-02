#pragma once

#include "render/RHI.h"
#include "core/Window.h"

namespace RenderingDEMO
{
	class OpenGLRHI :public RHI
	{
	public:
		OpenGLRHI() = default;
		~OpenGLRHI();

		virtual void Initialize(std::shared_ptr<Window> window) override;

		virtual void CreateSwapChain() override;
		virtual void RecreateSwapChain() override;

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(void* data, unsigned int size) override;
		virtual void CreateIndexBuffer() override;
		virtual void CreateShader() override;
		virtual void CreateVertexDeclaration() override;

		virtual void SetVertexShaderLayout() override;
		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) override;

		virtual void ClearBackBuffer(float r, float g, float b, float a) override;
		virtual void SwapBuffer() override;
		virtual void Draw() override;

	private:
		GLFWwindow* m_Window = nullptr;
		std::array<int, 2> m_WindowSize;

		unsigned int m_VAO = 0;
	};
}