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

		virtual void RecreateSwapChain(int width, int height) override;

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(void* data, unsigned int size) override;
		virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(void* data, unsigned int size) override;
		virtual std::shared_ptr<VertexDeclaration> CreateVertexDeclaration(const std::vector<VertexElement>& elements) override;
		virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::wstring& filePath) override;
		virtual std::shared_ptr<PixelShader> CreatePixelShader(const std::wstring& filePath) override;
		virtual std::shared_ptr<BoundShaderState> CreateBoundShaderState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd) override;

		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>) override;
		virtual void SetVertexLayout(std::shared_ptr<VertexDeclaration> vd) override;
		virtual void SetBoundShaderState(std::shared_ptr<BoundShaderState> state) override;

		virtual void ClearBackBuffer() override;
		virtual void SwapBuffer() override;
		virtual void Draw(unsigned int count) override;

	private:
		std::string ReadFromFile(const std::wstring& filePath);

	private:
		GLFWwindow* m_Window = nullptr;
		std::array<int, 2> m_WindowSize = {0 ,0};

		unsigned int m_VAO = 0;
	};
}