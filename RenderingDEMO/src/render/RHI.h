#pragma once

#include "core/Window.h"
#include "RHIResource.h"
#include "RHIState.h"

namespace RenderingDEMO
{
	class RHI
	{
	public:
		virtual ~RHI() = default;

		virtual void Initialize(std::shared_ptr<Window> window) = 0;

		virtual void RecreateSwapChain(int width, int height) = 0;

		virtual std::shared_ptr<RasterizerState> CreateRasterizerState(const RasterizerStateInitializer& initializer) = 0;
		virtual std::shared_ptr<DepthStencilState> CreateDepthStencilState(const DepthStencilStateInitializer& initializer) = 0;
		virtual std::shared_ptr<SamplerState> CreateSamplerState(const SamplerStateInitializer& initializer) = 0;

		virtual std::shared_ptr<Texture2D> CreateTexture2D(unsigned int width, unsigned int height, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, const void* data) = 0;

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void* data, unsigned int size, unsigned int stride) = 0;
		virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(const void* data, unsigned int size) = 0;
		virtual std::shared_ptr<UniformBuffer> CreateUniformBuffer(unsigned int size) = 0;

		virtual std::shared_ptr<VertexDeclaration> CreateVertexDeclaration(const std::vector<VertexElement>& elements) = 0;

		virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::wstring& fileName) = 0;
		virtual std::shared_ptr<PixelShader> CreatePixelShader(const std::wstring& fileName) = 0;
		
		virtual std::shared_ptr<RenderTarget> CreateRenderTarget(std::shared_ptr<Texture2D> colorTex, std::shared_ptr<Texture2D> depthTex) = 0;
		
		virtual std::shared_ptr<PipelineState> CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd, std::shared_ptr<RasterizerState> rasterState, std::shared_ptr<DepthStencilState> depthState) = 0;

		virtual void UpdateUniformBuffer(std::shared_ptr<UniformBuffer> ub, const void* data) = 0;

		virtual void SetTexture(std::shared_ptr<Texture> texture, unsigned int index) = 0;
		virtual void SetSamplerState(std::shared_ptr<SamplerState> sampler, unsigned int index) = 0;
		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) = 0;
		virtual void SetUniformBuffer(std::shared_ptr<UniformBuffer> ub, unsigned int index) = 0;
		virtual void SetRenderTarget(std::shared_ptr<RenderTarget> rt) = 0;
		virtual void SetViewPort(float width, float height) = 0;
		virtual void SetPipelineState(std::shared_ptr<PipelineState> state) = 0;

		virtual void ClearBackBuffer() = 0;
		virtual void ClearRenderTarget(std::shared_ptr<RenderTarget> target) = 0;
		virtual void SwapBuffer() = 0;
		virtual void Draw(unsigned int count) = 0;
		virtual void DrawIndexed(std::shared_ptr<IndexBuffer> ib) = 0;
		// virtual void DrawIndexedInstance() = 0;
	};
}