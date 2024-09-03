#pragma once

#include "render/RHI.h"
#include "core/Window.h"

//TODO: temp
#include <d3d11.h>
#include <dxgi1_3.h>

namespace RenderingDEMO
{
	class DirectXRHI :public RHI
	{
	public:
		~DirectXRHI();

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
		void CreateSwapChainResource();
		bool CompileShader(const std::wstring& filePath, const std::string& profile, Microsoft::WRL::ComPtr<ID3DBlob>& shaderBlob);

		DXGI_FORMAT FindTextureResourceDXGIFormat(TextureFormat resFormat);
		DXGI_FORMAT FindShaderResourceDXGIFormat(DXGI_FORMAT resFormat);
		DXGI_FORMAT FindDepthStencilDXGIFormat(DXGI_FORMAT resFormat);

		D3D11_TEXTURE_ADDRESS_MODE TranslateAddressMode(SamplerAddressMode addressMode);
		D3D11_CULL_MODE TranslateCullMode(RasterizerCullMode cullMode);
		D3D11_FILL_MODE TranslateFillMode(RasterizerFillMode fillMode);
		D3D11_COMPARISON_FUNC TranslateCompareFunction(DepthCompareFunc compareFunc);
		D3D11_FILTER TranslateSamplerFilter(SamplerFilter filter);

	private:
		HWND m_WindowHandler = nullptr;
		std::array<int, 2> m_WindowSize = { 0, 0 };

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGIFactory2> m_DXGIFactory;

		// temp: change to viewport
		Microsoft::WRL::ComPtr<IDXGISwapChain1> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_SwapChainRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_SwapChainDepthTarget;
	};
}