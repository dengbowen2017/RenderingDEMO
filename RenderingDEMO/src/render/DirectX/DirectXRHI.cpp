#include "DirectXRHI.h"
#include "DirectXRHIResource.h"
#include "DirectXRHIState.h"

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
	}

	void DirectXRHI::RecreateSwapChain(int width, int height)
	{
		m_WindowSize = { width, height };
		m_DeviceContext->Flush();
		m_SwapChainRenderTarget.Reset();
		m_SwapChainDepthTarget.Reset();

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
	}

	std::shared_ptr<RasterizerState> DirectXRHI::CreateRasterizerState(const RasterizerStateInitializer& initializer)
	{
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterState;

		D3D11_RASTERIZER_DESC rasterizerStateDescriptor = {};
		rasterizerStateDescriptor.DepthBias = 0;
		rasterizerStateDescriptor.DepthBiasClamp = 0.0f;
		rasterizerStateDescriptor.SlopeScaledDepthBias = 0.0f;
		rasterizerStateDescriptor.FrontCounterClockwise = true;
		rasterizerStateDescriptor.AntialiasedLineEnable = false;
		rasterizerStateDescriptor.MultisampleEnable = false;
		rasterizerStateDescriptor.DepthClipEnable = true;
		rasterizerStateDescriptor.ScissorEnable = false;
		rasterizerStateDescriptor.FillMode = TranslateFillMode(initializer.FillMode);
		rasterizerStateDescriptor.CullMode = TranslateCullMode(initializer.CullMode);

		if (FAILED(m_Device->CreateRasterizerState(&rasterizerStateDescriptor, rasterState.GetAddressOf())))
		{
			spdlog::error("D3D11: Failed to create rasterizer state");
			return nullptr;
		}

		DirectXRasterizerState* state = new DirectXRasterizerState;
		state->m_RasterizerState = rasterState;

		return std::shared_ptr<DirectXRasterizerState>(state);
	}

	std::shared_ptr<DepthStencilState> DirectXRHI::CreateDepthStencilState(const DepthStencilStateInitializer& initializer)
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthState;

		D3D11_DEPTH_STENCIL_DESC depthDesc{};
		depthDesc.DepthEnable = TRUE;
		depthDesc.DepthFunc = TranslateCompareFunction(initializer.DepthTest);
		depthDesc.DepthWriteMask = initializer.EnableDepthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;

		if (FAILED(m_Device->CreateDepthStencilState(&depthDesc, depthState.GetAddressOf())))
		{
			spdlog::error("D3D11: Failed to create depth stencil state");
			return nullptr;
		}

		DirectXDepthStencilState* state = new DirectXDepthStencilState;
		state->m_DepthStencilState = depthState;

		return std::shared_ptr<DirectXDepthStencilState>(state);
	}

	std::shared_ptr<SamplerState> DirectXRHI::CreateSamplerState(const SamplerStateInitializer& initializer)
	{
		Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = TranslateSamplerFilter(initializer.Filter);
		samplerDesc.AddressU = TranslateAddressMode(initializer.AddressU);
		samplerDesc.AddressV = TranslateAddressMode(initializer.AddressV);
		samplerDesc.AddressW = TranslateAddressMode(initializer.AddressW);

		if (FAILED(m_Device->CreateSamplerState(&samplerDesc, samplerState.GetAddressOf())))
		{
			spdlog::error("D3D11: Failed to create sampler state");
			return nullptr;
		}

		DirectXSamplerState* state = new DirectXSamplerState;
		state->m_SamplerState = samplerState;

		return std::shared_ptr<DirectXSamplerState>(state);
	}

	std::shared_ptr<Texture2D> DirectXRHI::CreateTexture2D(unsigned int width, unsigned int height, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, const void* data)
	{
		D3D11_TEXTURE2D_DESC texDesc = {};
		D3D11_SUBRESOURCE_DATA subData = {};
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texResource = nullptr;
		bool createRTV = false;
		bool createDSV = false;
		bool createSRV = false;

		unsigned int bindFlags = 0;
		if (flags & (unsigned int)TextureFlags::TexRenderTarget)
		{
			bindFlags |= D3D11_BIND_RENDER_TARGET;
			createRTV = true;
		}
		if (flags & (unsigned int)TextureFlags::TexDepthStencilTarget)
		{
			bindFlags |= D3D11_BIND_DEPTH_STENCIL;
			createDSV = true;
		}
		if (flags & (unsigned int)TextureFlags::TexShaderResource)
		{
			bindFlags |= D3D11_BIND_SHADER_RESOURCE;
			createSRV = true;
		}

		D3D11_USAGE usageFlag = D3D11_USAGE_DEFAULT;
		if (flags & (unsigned int)TextureFlags::TexDefault)
		{
			usageFlag = D3D11_USAGE_DEFAULT;
		}
		if (flags & (unsigned int)TextureFlags::TexImmutable)
		{
			usageFlag = D3D11_USAGE_IMMUTABLE;
		}

		DXGI_FORMAT texFormat = FindTextureResourceDXGIFormat(format);

		texDesc.Width = width;
		texDesc.Height = height;
		texDesc.MipLevels = numMips;
		texDesc.ArraySize = 1;
		texDesc.Format = texFormat;
		texDesc.SampleDesc.Count = numSamples;
		texDesc.Usage = usageFlag;
		texDesc.BindFlags = bindFlags;

		if (data != nullptr)
		{
			subData.pSysMem = data;
			if (texFormat == DXGI_FORMAT_R8_UNORM)
			{
				subData.SysMemPitch = width;
			}
			else if (texFormat == DXGI_FORMAT_R8G8_UNORM)
			{
				subData.SysMemPitch = 2 * width;
			}
			else if (texFormat == DXGI_FORMAT_R8G8B8A8_UNORM)
			{
				subData.SysMemPitch = 4 * width;
			}
		}

		if (FAILED(m_Device->CreateTexture2D(&texDesc, data != nullptr ? &subData : nullptr, texResource.GetAddressOf())))
		{
			spdlog::error("D3D11: Failed to create texture resource");
			return nullptr;
		}

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> texRTV = nullptr;
		if (createRTV)
		{
			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
			rtvDesc.Format = FindShaderResourceDXGIFormat(texFormat);
			rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

			if (FAILED(m_Device->CreateRenderTargetView(texResource.Get(), &rtvDesc, texRTV.GetAddressOf())))
			{
				spdlog::error("D3D11: Failed to create texture RTV");
				return nullptr;
			}
		}

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> texDSV = nullptr;
		if (createDSV)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
			dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

			if (FAILED(m_Device->CreateDepthStencilView(texResource.Get(), &dsvDesc, texDSV.GetAddressOf())))
			{
				spdlog::error("D3D11: Failed to create texture DSV");
				return nullptr;
			}
		}

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texSRV = nullptr;
		if (createSRV)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Format = FindShaderResourceDXGIFormat(texFormat);
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = numMips;

			if (FAILED(m_Device->CreateShaderResourceView(texResource.Get(), &srvDesc, texSRV.GetAddressOf())))
			{
				spdlog::error("D3D11: Failed to create texture SRV");
				return nullptr;
			}
		}

		return std::shared_ptr<DirectXTexture2D>(new DirectXTexture2D(width, height, numMips, numSamples, flags, format, texResource, texSRV, texRTV, texDSV));
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

	std::shared_ptr<VertexShader> DirectXRHI::CreateVertexShader(const std::wstring& fileName)
	{
		std::wstring filePath = fileName + L".hlsl";

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

	std::shared_ptr<PixelShader> DirectXRHI::CreatePixelShader(const std::wstring& fileName)
	{
		std::wstring filePath = fileName + L".hlsl";

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

	std::shared_ptr<PipelineState> DirectXRHI::CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd, std::shared_ptr<RasterizerState> rasterState, std::shared_ptr<DepthStencilState> depthState)
	{
		std::shared_ptr<DirectXVertexShader> dxvs = std::dynamic_pointer_cast<DirectXVertexShader>(vs);
		std::shared_ptr<DirectXPixelShader> dxps = std::dynamic_pointer_cast<DirectXPixelShader>(ps);
		std::shared_ptr<DirectXVertexDeclaration> dxvd = std::dynamic_pointer_cast<DirectXVertexDeclaration>(vd);
		std::shared_ptr<DirectXRasterizerState> dxrasterState = std::dynamic_pointer_cast<DirectXRasterizerState>(rasterState);
		std::shared_ptr<DirectXDepthStencilState> dxdepthState = std::dynamic_pointer_cast<DirectXDepthStencilState>(depthState);

		return std::shared_ptr<DirectXPipelineState>(new DirectXPipelineState(dxvs, dxps, dxvd, dxrasterState, dxdepthState, m_Device));
	}

	void DirectXRHI::UpdateUniformBuffer(std::shared_ptr<UniformBuffer> ub, const void* data)
	{
		std::shared_ptr<DirectXUniformBuffer> dxub = std::dynamic_pointer_cast<DirectXUniformBuffer>(ub);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		m_DeviceContext->Map(dxub->GetBuffer().Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, data, dxub->GetSize());
		m_DeviceContext->Unmap(dxub->GetBuffer().Get(), 0);
	}

	void DirectXRHI::SetTexture(std::shared_ptr<Texture> texture, unsigned int index)
	{
		std::shared_ptr<DirectXTexture2D> dxtex = std::dynamic_pointer_cast<DirectXTexture2D>(texture);

		// TODO: find a better way
		// have to treat uniform texture as global parameter (same as OpenGL)
		m_DeviceContext->VSSetShaderResources(index, 1, dxtex->GetShaderResourceView().GetAddressOf());
		m_DeviceContext->PSSetShaderResources(index, 1, dxtex->GetShaderResourceView().GetAddressOf());
	}

	void DirectXRHI::SetSamplerState(std::shared_ptr<SamplerState> sampler, unsigned int index)
	{
		std::shared_ptr<DirectXSamplerState> dxsampler = std::dynamic_pointer_cast<DirectXSamplerState>(sampler);

		// TODO: find a better way
		// have to treat uniform texture sampler as global parameter (same as OpenGL)
		m_DeviceContext->VSSetSamplers(index, 1, dxsampler->m_SamplerState.GetAddressOf());
		m_DeviceContext->PSSetSamplers(index, 1, dxsampler->m_SamplerState.GetAddressOf());
	}

	void DirectXRHI::SetVertexBuffer(std::shared_ptr<VertexBuffer> vb)
	{
		std::shared_ptr<DirectXVertexBuffer> dxvb = std::dynamic_pointer_cast<DirectXVertexBuffer>(vb);

		// temp
		// need a variable as the offset
		unsigned int offset = 0;
		unsigned int stride = dxvb->GetStride();
		m_DeviceContext->IASetVertexBuffers(0, 1, dxvb->GetBuffer().GetAddressOf(), &stride, &offset);
	}

	void DirectXRHI::SetUniformBuffer(std::shared_ptr<UniformBuffer> ub, unsigned int index)
	{
		std::shared_ptr<DirectXUniformBuffer> dxub = std::dynamic_pointer_cast<DirectXUniformBuffer>(ub);

		// TODO: find a better way
		// have to treat dxConstantBuffer as global parameter (same as OpenGL)
		m_DeviceContext->VSSetConstantBuffers(index, 1, dxub->GetBuffer().GetAddressOf());
		m_DeviceContext->PSSetConstantBuffers(index, 1, dxub->GetBuffer().GetAddressOf());
	}

	void DirectXRHI::SetRenderTarget(std::shared_ptr<RenderTarget> rt)
	{
		if (rt == nullptr)
		{
			m_DeviceContext->OMSetRenderTargets(1, m_SwapChainRenderTarget.GetAddressOf(), m_SwapChainDepthTarget.Get());
		}
	}

	void DirectXRHI::SetViewPort(float width, float height)
	{
		D3D11_VIEWPORT viewport = {};
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = width;
		viewport.Height = height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		m_DeviceContext->RSSetViewports(1, &viewport);
	}

	void DirectXRHI::SetPipelineState(std::shared_ptr<PipelineState> state)
	{
		std::shared_ptr<DirectXPipelineState> dxState = std::dynamic_pointer_cast<DirectXPipelineState>(state);

		m_DeviceContext->IASetInputLayout(dxState->m_InputLayout.Get());
		m_DeviceContext->VSSetShader(dxState->m_VertexShader.Get(), nullptr, 0);
		m_DeviceContext->PSSetShader(dxState->m_PixelShader.Get(), nullptr, 0);
		m_DeviceContext->RSSetState(dxState->m_RasterizerState.Get());
		m_DeviceContext->OMSetDepthStencilState(dxState->m_DepthStencilState.Get(), 0);
	}

	void DirectXRHI::ClearBackBuffer()
	{
		constexpr float clearColor[] = { 0.01f, 0.01f, 0.01f, 1.0f };
		ID3D11RenderTargetView* nullRTV = nullptr;

		m_DeviceContext->OMSetRenderTargets(1, &nullRTV, nullptr);
		m_DeviceContext->ClearRenderTargetView(m_SwapChainRenderTarget.Get(), clearColor);
		m_DeviceContext->ClearDepthStencilView(m_SwapChainDepthTarget.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void DirectXRHI::SwapBuffer()
	{
		m_SwapChain->Present(1, 0);
	}

	void DirectXRHI::Draw(unsigned int count)
	{
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_DeviceContext->Draw(count, 0);
	}

	void DirectXRHI::DrawIndexed(std::shared_ptr<IndexBuffer> ib)
	{
		std::shared_ptr<DirectXIndexBuffer> dxib = std::dynamic_pointer_cast<DirectXIndexBuffer>(ib);

		// temp
		unsigned int offset = 0;
		m_DeviceContext->IASetIndexBuffer(
			dxib->GetBuffer().Get(),
			DXGI_FORMAT_R32_UINT,
			offset
		);

		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_DeviceContext->DrawIndexed(dxib->GetCount(), 0, 0);
	}

	void DirectXRHI::CreateSwapChainResource()
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer = nullptr;
		if (FAILED(m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))))
		{
			spdlog::error("D3D11: Failed to get Back Buffer from the SwapChain");
			return;
		}

		if (FAILED(m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_SwapChainRenderTarget)))
		{
			spdlog::error("D3D11: Failed to create RTV from Back Buffer");
			return;
		}

		unsigned int flags = (unsigned int)TextureFlags::TexDepthStencilTarget;
		TextureFormat format = TextureFormat::R32_Typeless;
		std::shared_ptr<DirectXTexture2D> texture = std::dynamic_pointer_cast<DirectXTexture2D>(CreateTexture2D(m_WindowSize[0], m_WindowSize[1], 1, 1, flags, format, nullptr));
		m_SwapChainDepthTarget = texture->GetDepthStencilView();

		SetViewPort(static_cast<float>(m_WindowSize[0]), static_cast<float>(m_WindowSize[1]));
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

	DXGI_FORMAT DirectXRHI::FindTextureResourceDXGIFormat(TextureFormat resFormat)
	{
		switch (resFormat)
		{
		case TextureFormat::Unknow:
			return DXGI_FORMAT_UNKNOWN;
		case TextureFormat::R8_UNorm:
			return DXGI_FORMAT_R8_UNORM;
		case TextureFormat::R8G8_UNorm:
			return DXGI_FORMAT_R8G8_UNORM;
		case TextureFormat::R8G8B8A8_UNorm:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case TextureFormat::R32_Typeless:
			return DXGI_FORMAT_R32_TYPELESS;
		case TextureFormat::R24G8_Typeless:
			return DXGI_FORMAT_R24G8_TYPELESS;
		case TextureFormat::R16G16B16A16_Float:
			return DXGI_FORMAT_R16G16B16A16_FLOAT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	DXGI_FORMAT DirectXRHI::FindShaderResourceDXGIFormat(DXGI_FORMAT resFormat)
	{
		switch (resFormat)
		{
		case DXGI_FORMAT_R24G8_TYPELESS: 
			return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case DXGI_FORMAT_R32_TYPELESS: 
			return DXGI_FORMAT_R32_FLOAT;
		}
		return resFormat;
	}

	DXGI_FORMAT DirectXRHI::FindDepthStencilDXGIFormat(DXGI_FORMAT resFormat)
	{
		switch (resFormat)
		{
		case DXGI_FORMAT_R24G8_TYPELESS:
			return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case DXGI_FORMAT_R32_TYPELESS:
			return DXGI_FORMAT_D32_FLOAT;
		}
		return resFormat;
	}

	D3D11_TEXTURE_ADDRESS_MODE DirectXRHI::TranslateAddressMode(SamplerAddressMode addressMode)
	{
		switch (addressMode)
		{
		case SamplerAddressMode::Mirror:
			return D3D11_TEXTURE_ADDRESS_MIRROR;
		case SamplerAddressMode::Clamp:
			return D3D11_TEXTURE_ADDRESS_CLAMP;
		default:
			return D3D11_TEXTURE_ADDRESS_WRAP;
		}
	}

	D3D11_CULL_MODE DirectXRHI::TranslateCullMode(RasterizerCullMode cullMode)
	{
		switch (cullMode)
		{
		case RasterizerCullMode::Front:
			return D3D11_CULL_FRONT;
		case RasterizerCullMode::Back:
			return D3D11_CULL_BACK;
		default:
			return D3D11_CULL_NONE;
		}
	}

	D3D11_FILL_MODE DirectXRHI::TranslateFillMode(RasterizerFillMode fillMode)
	{
		switch (fillMode)
		{
		case RasterizerFillMode::Wireframe:
			return D3D11_FILL_WIREFRAME;
		default:
			return D3D11_FILL_SOLID;
		}
	}

	D3D11_COMPARISON_FUNC DirectXRHI::TranslateCompareFunction(DepthCompareFunc compareFunc)
	{
		switch (compareFunc)
		{
		case DepthCompareFunc::Less:
			return D3D11_COMPARISON_LESS;
		case DepthCompareFunc::LessEqual:
			return D3D11_COMPARISON_LESS_EQUAL;
		case DepthCompareFunc::Greater:
			return D3D11_COMPARISON_GREATER;
		case DepthCompareFunc::GreaterEqual:
			return D3D11_COMPARISON_GREATER_EQUAL;
		default:
			return D3D11_COMPARISON_ALWAYS;
		}
	}

	D3D11_FILTER DirectXRHI::TranslateSamplerFilter(SamplerFilter filter)
	{
		switch (filter)
		{
		case SamplerFilter::Nearest:
			return D3D11_FILTER_MIN_MAG_MIP_POINT;
		case SamplerFilter::Bilinear:
			return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		case SamplerFilter::Trilinear:
			return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		default:
			return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		}
	}
}