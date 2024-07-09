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

		virtual std::shared_ptr<RasterizerState> CreateRasterizerState() override;
		virtual std::shared_ptr<DepthStencilState> CreateDepthStencilState() override;

		virtual std::shared_ptr<Texture2D> CreateTexture2D(unsigned int width, unsigned int height, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, const void* data) override;

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void* data, unsigned int size, unsigned int stride) override;
		virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(const void* data, unsigned int size) override;
		virtual std::shared_ptr<UniformBuffer> CreateUniformBuffer(unsigned int size) override;
		virtual std::shared_ptr<VertexDeclaration> CreateVertexDeclaration(const std::vector<VertexElement>& elements) override;
		virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::wstring& filePath) override;
		virtual std::shared_ptr<PixelShader> CreatePixelShader(const std::wstring& filePath) override;

		virtual std::shared_ptr<PipelineState> CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd, std::shared_ptr<RasterizerState> rasterState, std::shared_ptr<DepthStencilState> depthState) override;

		virtual void UpdateUniformBuffer(std::shared_ptr<UniformBuffer> ub, const void* data) override;

		virtual void SetTexture(std::shared_ptr<Texture> texture, unsigned int index) override;
		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) override;
		virtual void SetUniformBuffer(std::shared_ptr<UniformBuffer> ub, unsigned int index) override;
		virtual void SetPipelineState(std::shared_ptr<PipelineState> state) override;

		virtual void ClearBackBuffer() override;
		virtual void SwapBuffer() override;
		virtual void Draw(unsigned int count) override;
		virtual void DrawIndexed(std::shared_ptr<IndexBuffer> ib) override;

	private:
		std::string ReadFromFile(const std::wstring& filePath);

	private:
		GLFWwindow* m_Window = nullptr;
		std::array<int, 2> m_WindowSize = {0 ,0};

		// part of the context
		unsigned int m_VAO = 0;
	};
}