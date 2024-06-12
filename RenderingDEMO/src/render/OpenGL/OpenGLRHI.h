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

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(void* data, unsigned int size, unsigned int stride) override;
		virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(void* data, unsigned int size) override;
		virtual std::shared_ptr<VertexDeclaration> CreateVertexDeclaration(const std::vector<VertexElement>& elements) override;
		virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::wstring& filePath) override;
		virtual std::shared_ptr<PixelShader> CreatePixelShader(const std::wstring& filePath) override;
		virtual std::shared_ptr<PipelineState> CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd) override;

		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) override;
		virtual void SetPipelineState(std::shared_ptr<PipelineState> state) override;

		virtual void ClearBackBuffer() override;
		virtual void SwapBuffer() override;
		virtual void Draw(std::shared_ptr<IndexBuffer> ib) override;

	private:
		std::string ReadFromFile(const std::wstring& filePath);

	private:
		GLFWwindow* m_Window = nullptr;
		std::array<int, 2> m_WindowSize = {0 ,0};

		// part of the context
		unsigned int m_VAO = 0;
	};
}