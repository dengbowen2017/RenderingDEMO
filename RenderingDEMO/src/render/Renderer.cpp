#include "Renderer.h"
#include "render/OpenGL/OpenGLRHI.h"
#include "render/DirectX/DirectXRHI.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize(std::shared_ptr<Window> window, RenderAPI api)
	{
		switch (api)
		{
		case RenderAPI::Unknown:
			spdlog::error("Unknown RenderAPI");
			break;
		case RenderAPI::OpenGL:
			m_RHI = std::make_shared<OpenGLRHI>();
			break;
		case RenderAPI::DirectX:
			m_RHI = std::make_shared<DirectXRHI>();
			break;
		}

		m_RHI->Initialize(window);

		m_RenderResource = std::make_shared<RenderResource>();

		//m_WindowUI = std::make_shared<WindowUI>();
		//m_WindowUI->Initialize(window);

		PreProcess();
		SetPipline();
	}

	void Renderer::OnUpdate()
	{
		m_RHI->ClearBackBuffer();
		//m_WindowUI->OnUpdate();
		m_RHI->Draw();
		m_RHI->SwapBuffer();
	}

	void Renderer::PreProcess()
	{
		float vertices[] =
		{
			 0.0f,  0.5f, 0.0f, 0.2f, 0.7f, 0.4f,
			 0.5f, -0.5f, 0.0f, 0.9f, 0.2f, 0.6f,
			-0.5f, -0.5f, 0.0f, 0.3f, 0.9f, 0.8f
		};

		// anticlockwise is the default setting for OpenGL
		// clockwise is the default setting for DirectX
		// set rasterizer state to change to anticlockwise
		unsigned int indices[] =
		{
			2, 1, 0
		};

		std::vector<VertexElement> elements;
		elements.push_back({ "POSITION", 0, VertexElementType::Float3 });
		elements.push_back({ "COLOR", 0, VertexElementType::Float3 });

		std::shared_ptr<VertexBuffer> vb = m_RHI->CreateVertexBuffer(vertices, sizeof(vertices));
		std::shared_ptr<IndexBuffer> ib = m_RHI->CreateIndexBuffer(indices, sizeof(indices));
		std::shared_ptr<VertexDeclaration> vd = m_RHI->CreateVertexDeclaration(elements);
		std::shared_ptr<VertexShader> vs = m_RHI->CreateVertexShader(L"../shader/vs.hlsl");
		std::shared_ptr<PixelShader> ps = m_RHI->CreatePixelShader(L"../shader/ps.hlsl");
		std::shared_ptr<BoundShaderState> ss = m_RHI->CreateBoundShaderState(vs, ps, vd);

		m_RenderResource->m_VertexBuffers.push_back(vb);
		m_RenderResource->m_IndexBuffers.push_back(ib);
		m_RenderResource->m_VertexDeclarations.insert({ "default", vd });
		m_RenderResource->m_VertexShaders.insert({ "default", vs });
		m_RenderResource->m_PixelShaders.insert({ "default" , ps });
		m_RenderResource->m_BoundShaderStates.insert({ "default" , ss });
	}

	void Renderer::SetPipline()
	{
		m_RHI->SetBoundShaderState(m_RenderResource->m_BoundShaderStates["default"]);
		m_RHI->SetVertexBuffer(m_RenderResource->m_VertexBuffers[0]);
		m_RHI->SetIndexBuffer(m_RenderResource->m_IndexBuffers[0]);
	}
}