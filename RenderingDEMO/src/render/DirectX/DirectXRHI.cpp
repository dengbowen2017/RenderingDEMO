#include "DirectXRHI.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	DirectXRHI::~DirectXRHI()
	{
	}

	void DirectXRHI::Initialize(std::shared_ptr<Window> window)
	{
		m_WindowHandler = window->GetWindowHandler();
		m_WindowSize = window->GetWindowSize();
		
		//Create DXGIFactory
		if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactory))))
		{
			spdlog::error("Failed to create DXGIFactory");
			return;
		}

		//Create D3DDevice
		constexpr D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
		if (FAILED(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			&deviceFeatureLevel,
			1,
			D3D11_SDK_VERSION,
			&m_Device,
			nullptr,
			&m_DeviceContext)))
		{
			spdlog::error("Failed to create device and device context");
			return;
		}

		//Create SwapChain
		DXGI_SWAP_CHAIN_DESC1 scd = {};
		scd.Width = m_WindowSize[0];
		scd.Height = m_WindowSize[1];
		scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 2;
		scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		scd.Scaling = DXGI_SCALING_STRETCH;
		scd.Flags = {};

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC scfd = {};
		scfd.Windowed = true;

		if (FAILED(m_DXGIFactory->CreateSwapChainForHwnd(
			m_Device.Get(),
			m_WindowHandler,
			&scd,
			&scfd,
			nullptr,
			&m_SwapChain)))
		{
			spdlog::error("Failed to create swapchain");
			return;
		}
		
		CreateSwapChainResource();
	}

	void DirectXRHI::RecreateSwapChain(int width, int height)
	{
		m_WindowSize = { width, height };
		m_DeviceContext->Flush();
		m_RenderTarget.Reset();
		if (FAILED(m_SwapChain->ResizeBuffers(
			0,
			width,
			height,
			DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM,
			0)))
		{
			spdlog::error("Failed to recreate SwapChain buffers");
			return;
		}

		CreateSwapChainResource();
		spdlog::info("Window Size:{0}, {1}", m_WindowSize[0], m_WindowSize[1]);
	}

	std::shared_ptr<VertexBuffer> DirectXRHI::CreateVertexBuffer(void* data, unsigned int size)
	{
		return std::shared_ptr<VertexBuffer>();
	}

	std::shared_ptr<IndexBuffer> DirectXRHI::CreateIndexBuffer(void* data, unsigned int size)
	{
		return std::shared_ptr<IndexBuffer>();
	}

	std::shared_ptr<VertexDeclaration> DirectXRHI::CreateVertexDeclaration(const std::vector<VertexElement>& elements)
	{
		return std::shared_ptr<VertexDeclaration>();
	}

	std::shared_ptr<VertexShader> DirectXRHI::CreateVertexShader(const std::string& file_path)
	{
		return std::shared_ptr<VertexShader>();
	}

	std::shared_ptr<PixelShader> DirectXRHI::CreatePixelShader(const std::string& file_path)
	{
		return std::shared_ptr<PixelShader>();
	}

	std::shared_ptr<BoundShaderState> DirectXRHI::CreateBoundShaderState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd)
	{
		return std::shared_ptr<BoundShaderState>();
	}

	void DirectXRHI::SetVertexBuffer(std::shared_ptr<VertexBuffer> vb)
	{
	}

	void DirectXRHI::SetIndexBuffer(std::shared_ptr<IndexBuffer>)
	{
	}

	void DirectXRHI::SetVertexLayout(std::shared_ptr<VertexDeclaration> vd)
	{
	}

	void DirectXRHI::SetBoundShaderState(std::shared_ptr<BoundShaderState> state)
	{
	}

	void DirectXRHI::ClearBackBuffer()
	{
		constexpr float clearColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		m_DeviceContext->ClearRenderTargetView(m_RenderTarget.Get(), clearColor);
	}

	void DirectXRHI::SwapBuffer()
	{
		m_SwapChain->Present(1, 0);
	}

	void DirectXRHI::Draw(unsigned int count)
	{
	}

	void DirectXRHI::CreateSwapChainResource()
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer = nullptr;
		if (FAILED(m_SwapChain->GetBuffer(
			0,
			IID_PPV_ARGS(&backBuffer))))
		{
			spdlog::error("D3D11: Failed to get Back Buffer from the SwapChain");
			return;
		}

		if (FAILED(m_Device->CreateRenderTargetView(
			backBuffer.Get(),
			nullptr,
			&m_RenderTarget)))
		{
			spdlog::error("Failed to create RTV from Back Buffer");
			return;
		}

		SetViewportAndRenderTarget();
	}

	void DirectXRHI::SetViewportAndRenderTarget()
	{
		D3D11_VIEWPORT viewport = {};
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<float>(m_WindowSize[0]);
		viewport.Height = static_cast<float>(m_WindowSize[1]);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		m_DeviceContext->RSSetViewports(1, &viewport);
		m_DeviceContext->OMSetRenderTargets(1, m_RenderTarget.GetAddressOf(), nullptr);
	}
}