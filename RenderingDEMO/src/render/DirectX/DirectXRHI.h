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
		DirectXRHI() = default;
		~DirectXRHI();

		virtual void Initialize(std::shared_ptr<Window> window) override;

		//TODO: should change to swapChainResource since we only have to change the size of the back buffer rather than recreate the whole swapchain?
		virtual void RecreateSwapChain(int width, int height) override;

		virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void* data, unsigned int size, unsigned int stride) override;
		virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(const void* data, unsigned int size) override;
		virtual std::shared_ptr<UniformBuffer> CreateUniformBuffer(unsigned int size) override;
		virtual std::shared_ptr<VertexDeclaration> CreateVertexDeclaration(const std::vector<VertexElement>& elements) override;
		virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::wstring& filePath) override;
		virtual std::shared_ptr<PixelShader> CreatePixelShader(const std::wstring& filePath) override;
		virtual std::shared_ptr<PipelineState> CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd) override;

		virtual void UpdateUniformBuffer(std::shared_ptr<UniformBuffer> ub, const void* data) override;

		virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) override;
		virtual void SetUniformBuffer(std::shared_ptr<UniformBuffer> ub, unsigned int index) override;
		virtual void SetPipelineState(std::shared_ptr<PipelineState> state) override;

		virtual void ClearBackBuffer() override;
		virtual void SwapBuffer() override;
		virtual void Draw(std::shared_ptr<IndexBuffer> ib) override;

	private:
		void CreateSwapChainResource();
		void SetViewportAndRenderTarget();
		void CreateRasterizerStates();
		void CreateDepthStencilStates();
		void CreateDepthStencilView();
		bool CompileShader(const std::wstring& filePath, const std::string& profile, Microsoft::WRL::ComPtr<ID3DBlob>& shaderBlob);

	private:
		HWND m_WindowHandler = nullptr;
		std::array<int, 2> m_WindowSize = { 0 ,0 };

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGIFactory2> m_DXGIFactory;

		// temp
		Microsoft::WRL::ComPtr<IDXGISwapChain1> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RasterizerState;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthTarget;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
	};
}