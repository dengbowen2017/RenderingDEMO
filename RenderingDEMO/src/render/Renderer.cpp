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

		// temp
		switch (api)
		{
		case RenderAPI::OpenGL:
			m_Suffix = L".glsl";
			break;
		case RenderAPI::DirectX:
			m_Suffix = L".hlsl";
			break;
		}

		m_CurrentAPI = api;

		m_RHI->Initialize(window);

		m_RenderResource = std::make_shared<RenderResource>();

		//m_WindowUI = std::make_shared<WindowUI>();
		//m_WindowUI->Initialize(window);

		PreProcess();
		SetPipline();
	}

	void Renderer::OnUpdate()
	{
		// Do rendering similarly as DirectX12
		// Clear the color and depth buffers
			//For each object in the scene :
			//Transition any resources to the required state
			//Bind the Pipeline State Object(PSO)
			//Bind the Root Signature
			//Bind any resources(CBV, UAV, SRV, Samplers, etc..) to the shader stages
			//Set the primitive topology for the Input Assembler(IA)
			//Bind the vertex buffer to the IA
			//Bind the index buffer to the IA
			//Set the viewport(s) for the Rasterizer Stage(RS)
			//Set the scissor rectangle(s) for the RS
			//Bind the color and depth - stencil render targets to the Output Merger(OM)
			//Draw the geometry
		//Present the rendered image to the screen

		m_RHI->ClearBackBuffer();
		//m_WindowUI->OnUpdate();
		m_RHI->Draw(m_RenderResource->m_IndexBuffers[0]);
		m_RHI->SwapBuffer();
	}

	void Renderer::PreProcess()
	{
		float vertices[] =
		{
			 0.0f,  0.5f, 0.0f, 0.9f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.9f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.9f
		};

		// anticlockwise is the default setting for OpenGL
		// clockwise is the default setting for DirectX
		// set DirectX rasterizer state to anticlockwise
		unsigned int indices[] =
		{
			2, 1, 0
		};

		//VertexElement.Name is used in DirectX to set the SemanticName. OpenGL do not need this.
		//VertexElement.Index is only used in DirectX to set the SemanticIndex
		std::vector<VertexElement> elements;
		elements.push_back({ "POSITION", 0, VertexElementType::Float3 });
		elements.push_back({ "COLOR", 0, VertexElementType::Float3 });
		std::shared_ptr<VertexDeclaration> vd = m_RHI->CreateVertexDeclaration(elements);

		std::shared_ptr<VertexBuffer> vb = m_RHI->CreateVertexBuffer(vertices, sizeof(vertices), vd->GetStride());
		std::shared_ptr<IndexBuffer> ib = m_RHI->CreateIndexBuffer(indices, sizeof(indices));

		// temp file path
		std::shared_ptr<VertexShader> vs = m_RHI->CreateVertexShader(L"../shader/vs" + m_Suffix);
		std::shared_ptr<PixelShader> ps = m_RHI->CreatePixelShader(L"../shader/ps" + m_Suffix);

		std::shared_ptr<PipelineState> pips = m_RHI->CreatePipelineState(vs, ps, vd);

		m_RenderResource->m_VertexBuffers.push_back(vb);
		m_RenderResource->m_IndexBuffers.push_back(ib);
		m_RenderResource->m_VertexDeclarations.insert({ "default", vd });
		m_RenderResource->m_VertexShaders.insert({ "default", vs });
		m_RenderResource->m_PixelShaders.insert({ "default" , ps });
		m_RenderResource->m_PipelineState = pips;
	}

	void Renderer::SetPipline()
	{
		m_RHI->SetPipelineState(m_RenderResource->m_PipelineState);
		m_RHI->SetVertexBuffer(m_RenderResource->m_VertexBuffers[0]);
	}
}