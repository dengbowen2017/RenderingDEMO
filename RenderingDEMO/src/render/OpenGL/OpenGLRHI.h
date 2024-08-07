#pragma once

#include "render/RHI.h"
#include "core/Window.h"

// temp
#include <glad/glad.h>

namespace RenderingDEMO
{
	class OpenGLRHI :public RHI
	{
	public:
		~OpenGLRHI();

		virtual void Initialize(std::shared_ptr<Window> window) override;

		virtual void RecreateSwapChain(int width, int height) override;

		virtual std::shared_ptr<RasterizerState> CreateRasterizerState(const RasterizerStateInitializer& initializer) override;
		virtual std::shared_ptr<DepthStencilState> CreateDepthStencilState(const DepthStencilStateInitializer& initializer) override;
		virtual std::shared_ptr<SamplerState> CreateSamplerState(const SamplerStateInitializer& initializer) override;

		virtual std::shared_ptr<Texture2D> CreateTexture2D(unsigned int width, unsigned int height, unsigned int arraySize, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, ResourceRawData& rawData) override;

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void* data, unsigned int size, unsigned int stride) override;
		virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(const void* data, unsigned int size) override;
		virtual std::shared_ptr<UniformBuffer> CreateUniformBuffer(unsigned int size) override;

		virtual std::shared_ptr<VertexDeclaration> CreateVertexDeclaration(const std::vector<VertexElement>& elements) override;

		virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::wstring& fileName) override;
		virtual std::shared_ptr<PixelShader> CreatePixelShader(const std::wstring& fileName) override;

		virtual std::shared_ptr<RenderTarget> CreateRenderTarget(std::shared_ptr<Texture2D> colorTex, std::shared_ptr<Texture2D> depthTex) override;

		virtual std::shared_ptr<PipelineState> CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd, std::shared_ptr<RasterizerState> rasterState, std::shared_ptr<DepthStencilState> depthState) override;

		virtual void UpdateUniformBuffer(std::shared_ptr<UniformBuffer> ub, const void* data) override;

		virtual void SetTexture(std::shared_ptr<Texture> texture, unsigned int index) override;
		virtual void SetSamplerState(std::shared_ptr<SamplerState> sampler, unsigned int index) override;
		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) override;
		virtual void SetUniformBuffer(std::shared_ptr<UniformBuffer> ub, unsigned int index) override;
		virtual void SetRenderTarget(std::shared_ptr<RenderTarget> rt) override;
		virtual void SetViewPort(float width, float height) override;
		virtual void SetPipelineState(std::shared_ptr<PipelineState> state) override;

		virtual void ClearBackBuffer() override;
		virtual void ClearRenderTarget(std::shared_ptr<RenderTarget> target) override;
		virtual void SwapBuffer() override;
		virtual void Draw(unsigned int count) override;
		virtual void DrawIndexed(std::shared_ptr<IndexBuffer> ib) override;

	private:
		std::string ReadFromFile(const std::wstring& filePath);

		GLint FindTextureInternalFormat(TextureFormat format);
		GLenum FindTextureResourceFormat(GLint format);
		GLenum FindTextureResourceType(GLint format);

		GLint TranslateAddressMode(SamplerAddressMode addressMode);
		GLenum TranslateCullMode(RasterizerCullMode cullMode);
		GLenum TranslateFillMode(RasterizerFillMode fillMode);
		GLenum TranslateCompareFunction(DepthCompareFunc compareFunc);

	private:
		GLFWwindow* m_Window = nullptr;
		std::array<int, 2> m_WindowSize = {0, 0};

		// part of the context
		unsigned int m_VAO = 0;
	};
}