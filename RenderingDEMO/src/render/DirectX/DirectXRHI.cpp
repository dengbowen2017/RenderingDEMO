#include "DirectXRHI.h"
#include "DirectXRHIResource.h"

#include <d3dcompiler.h>

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

		// temp
		// Create RasterizerState
		CreateRasterizerStates();

		// Create DepthState
		CreateDepthStencilView();
		CreateDepthStencilStates();
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

		m_DepthTarget.Reset();
		CreateDepthStencilView();
	}

	std::shared_ptr<VertexBuffer> DirectXRHI::CreateVertexBuffer(const void* data, unsigned int size, unsigned int stride)
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> vb;

		D3D11_BUFFER_DESC bufferInfo = {};
		bufferInfo.ByteWidth = size;
		bufferInfo.Usage = D3D11_USAGE_IMMUTABLE;
		bufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA resourceData = {};
		resourceData.pSysMem = data;
		if (FAILED(m_Device->CreateBuffer(
			&bufferInfo,
			&resourceData,
			&vb)))
		{
			spdlog::error("D3D11: Failed to create vertex buffer");
			return false;
		}

		return std::shared_ptr<DirectXVertexBuffer>(new DirectXVertexBuffer(vb, size, stride));
	}

	std::shared_ptr<IndexBuffer> DirectXRHI::CreateIndexBuffer(const void* data, unsigned int size)
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> ib;

		D3D11_BUFFER_DESC bufferInfo = {};
		bufferInfo.ByteWidth = size;
		bufferInfo.Usage = D3D11_USAGE_IMMUTABLE;
		bufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA resourceData = {};
		resourceData.pSysMem = data;
		
		if (FAILED(m_Device->CreateBuffer(
			&bufferInfo,
			&resourceData,
			&ib)))
		{
			spdlog::error("D3D11: Failed to create index buffer");
			return false;
		}

		return std::shared_ptr<DirectXIndexBuffer>(new DirectXIndexBuffer(ib, size / sizeof(unsigned int)));
	}

	std::shared_ptr<UniformBuffer> DirectXRHI::CreateUniformBuffer(unsigned int size)
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> ub;

		D3D11_BUFFER_DESC bufferInfo = {};
		bufferInfo.ByteWidth = size;
		bufferInfo.Usage = D3D11_USAGE_DYNAMIC;
		bufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (FAILED(m_Device->CreateBuffer(
			&bufferInfo,
			nullptr,
			&ub)))
		{
			spdlog::error("D3D11: Failed to create constant buffer");
			return false;
		}

		return std::shared_ptr<DirectXUniformBuffer>(new DirectXUniformBuffer(ub, size));
	}

	std::shared_ptr<VertexDeclaration> DirectXRHI::CreateVertexDeclaration(const std::vector<VertexElement>& elements)
	{
		return std::shared_ptr<DirectXVertexDeclaration>(new DirectXVertexDeclaration(elements));
	}

	std::shared_ptr<VertexShader> DirectXRHI::CreateVertexShader(const std::wstring& filePath)
	{
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
		Microsoft::WRL::ComPtr<ID3D10Blob> blob;

		if (!CompileShader(filePath, "vs_5_0", blob))
		{
			return nullptr;
		}

		if (FAILED(m_Device->CreateVertexShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&vs)))
		{
			spdlog::error("D3D11: Failed to compile vertex shader");
			return nullptr;
		}

		return std::shared_ptr<DirectXVertexShader>(new DirectXVertexShader(vs, blob));
	}

	std::shared_ptr<PixelShader> DirectXRHI::CreatePixelShader(const std::wstring& filePath)
	{
		Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;
		Microsoft::WRL::ComPtr<ID3D10Blob> blob;

		if (!CompileShader(filePath, "ps_5_0", blob))
		{
			return nullptr;
		}

		if (FAILED(m_Device->CreatePixelShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&ps)))
		{
			spdlog::error("D3D11: Failed to compile Pixel shader");
			return nullptr;
		}

		return std::shared_ptr<DirectXPixelShader>(new DirectXPixelShader(ps));
	}

	std::shared_ptr<PipelineState> DirectXRHI::CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd)
	{
		std::shared_ptr<DirectXVertexShader> dxvs = std::dynamic_pointer_cast<DirectXVertexShader>(vs);
		std::shared_ptr<DirectXPixelShader> dxps = std::dynamic_pointer_cast<DirectXPixelShader>(ps);
		std::shared_ptr<DirectXVertexDeclaration> dxvd = std::dynamic_pointer_cast<DirectXVertexDeclaration>(vd);

		return std::shared_ptr<DirectXPipelineState>(new DirectXPipelineState(dxvs, dxps, dxvd, m_Device));
	}

	void DirectXRHI::UpdateUniformBuffer(std::shared_ptr<UniformBuffer> ub, const void* data)
	{
		std::shared_ptr<DirectXUniformBuffer> dxub = std::dynamic_pointer_cast<DirectXUniformBuffer>(ub);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		m_DeviceContext->Map(dxub->GetBuffer().Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, data, dxub->GetSize());
		m_DeviceContext->Unmap(dxub->GetBuffer().Get(), 0);
	}

	void DirectXRHI::SetVertexBuffer(std::shared_ptr<VertexBuffer> vb)
	{
		std::shared_ptr<DirectXVertexBuffer> dxvb = std::dynamic_pointer_cast<DirectXVertexBuffer>(vb);

		// temp
		// need a variable as the offset
		unsigned int offset = 0;
		unsigned int stride = dxvb->GetStride();
		m_DeviceContext->IASetVertexBuffers(
			0,
			1,
			dxvb->GetBuffer().GetAddressOf(),
			&stride,
			&offset
		);
	}

	void DirectXRHI::SetUniformBuffer(std::shared_ptr<UniformBuffer> ub, unsigned int index)
	{
		std::shared_ptr<DirectXUniformBuffer> dxub = std::dynamic_pointer_cast<DirectXUniformBuffer>(ub);

		// temp
		// bind uniform buffer to all shaders
		m_DeviceContext->VSSetConstantBuffers(index, 1, dxub->GetBuffer().GetAddressOf());
		m_DeviceContext->PSSetConstantBuffers(index, 1, dxub->GetBuffer().GetAddressOf());
	}

	void DirectXRHI::SetPipelineState(std::shared_ptr<PipelineState> state)
	{
		std::shared_ptr<DirectXPipelineState> dxState = std::dynamic_pointer_cast<DirectXPipelineState>(state);

		m_DeviceContext->IASetInputLayout(dxState->m_InputLayout.Get());
		m_DeviceContext->VSSetShader(dxState->m_VertexShader.Get(), nullptr, 0);
		m_DeviceContext->PSSetShader(dxState->m_PixelShader.Get(), nullptr, 0);
		m_DeviceContext->RSSetState(dxState->m_RasterizerState.Get());
		m_DeviceContext->IASetPrimitiveTopology(dxState->m_DrawType);
	}

	void DirectXRHI::ClearBackBuffer()
	{
		constexpr float clearColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		ID3D11RenderTargetView* nullRTV = nullptr;

		m_DeviceContext->OMSetRenderTargets(1, &nullRTV, nullptr);
		m_DeviceContext->ClearRenderTargetView(m_RenderTarget.Get(), clearColor);
		m_DeviceContext->ClearDepthStencilView(m_DepthTarget.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void DirectXRHI::SwapBuffer()
	{
		m_SwapChain->Present(1, 0);
	}

	void DirectXRHI::Draw(unsigned int count)
	{
		m_DeviceContext->OMSetRenderTargets(1, m_RenderTarget.GetAddressOf(), m_DepthTarget.Get());
		m_DeviceContext->Draw(count, 0);
	}

	void DirectXRHI::DrawIndexed(std::shared_ptr<IndexBuffer> ib)
	{
		std::shared_ptr<DirectXIndexBuffer> dxib = std::dynamic_pointer_cast<DirectXIndexBuffer>(ib);

		unsigned int offset = 0; 		// temp
		m_DeviceContext->IASetIndexBuffer(
			dxib->GetBuffer().Get(),
			DXGI_FORMAT_R32_UINT,
			offset
		);
	
		// need to set render target for every frame
		m_DeviceContext->OMSetRenderTargets(1, m_RenderTarget.GetAddressOf(), m_DepthTarget.Get());
		m_DeviceContext->DrawIndexed(dxib->GetCount(), 0, 0);
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
			spdlog::error("D3D11: Failed to create RTV from Back Buffer");
			return;
		}

		SetViewport();
	}

	void DirectXRHI::SetViewport()
	{
		D3D11_VIEWPORT viewport = {};
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<float>(m_WindowSize[0]);
		viewport.Height = static_cast<float>(m_WindowSize[1]);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		m_DeviceContext->RSSetViewports(1, &viewport);
	}

	void DirectXRHI::CreateRasterizerStates()
	{
		D3D11_RASTERIZER_DESC rasterizerStateDescriptor = {};
		rasterizerStateDescriptor.AntialiasedLineEnable = false;
		rasterizerStateDescriptor.DepthBias = 0;
		rasterizerStateDescriptor.DepthBiasClamp = 0.0f;
		rasterizerStateDescriptor.DepthClipEnable = false;
		rasterizerStateDescriptor.FrontCounterClockwise = true;
		rasterizerStateDescriptor.MultisampleEnable = false;
		rasterizerStateDescriptor.ScissorEnable = false;
		rasterizerStateDescriptor.SlopeScaledDepthBias = 0.0f;
		rasterizerStateDescriptor.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerStateDescriptor.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		if (FAILED(m_Device->CreateRasterizerState(&rasterizerStateDescriptor, &m_RasterizerState)))
		{
			spdlog::error("D3D11: Failed to create rasterizer state");
			return;
		}
	}

	void DirectXRHI::CreateDepthStencilStates()
	{
		D3D11_DEPTH_STENCIL_DESC depthDesc{};
		depthDesc.DepthEnable = TRUE;
		depthDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

		m_Device->CreateDepthStencilState(&depthDesc, &m_DepthStencilState);
	}

	void DirectXRHI::CreateDepthStencilView()
	{
		D3D11_TEXTURE2D_DESC texDesc{};
		texDesc.Height = m_WindowSize[1];
		texDesc.Width = m_WindowSize[0];
		texDesc.ArraySize = 1;
		texDesc.SampleDesc.Count = 1;
		texDesc.MipLevels = 1;
		texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		texDesc.Format = DXGI_FORMAT_R32_TYPELESS;

		ID3D11Texture2D* texture = nullptr;
		if (FAILED(m_Device->CreateTexture2D(&texDesc, nullptr, &texture)))
		{
			spdlog::error("D3D11: Failed to create texture for DepthStencilView");
			return;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		if (FAILED(m_Device->CreateDepthStencilView(texture, &dsvDesc, &m_DepthTarget)))
		{
			spdlog::error("D3D11: Failed to create DepthStencilView");
			texture->Release();
			return;
		}

		texture->Release();
	}

	bool DirectXRHI::CompileShader(const std::wstring& filePath, const std::string& profile, Microsoft::WRL::ComPtr<ID3DBlob>& shaderBlob)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> tempShaderBlob = nullptr;
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

		// temp
		// hard code entrypoint
		if (FAILED(D3DCompileFromFile(
			filePath.data(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			profile.data(),
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&tempShaderBlob,
			&errorBlob)))
		{
			spdlog::error("D3D11: Failed to read shader from file");
			if (errorBlob != nullptr)
			{
				spdlog::error("D3D11: With message: {0}", static_cast<const char*>(errorBlob->GetBufferPointer()));
			}
			return false;
		}

		shaderBlob = std::move(tempShaderBlob);
		return true;
	}
}