#include "Renderer.h"
#include "render/OpenGL/OpenGLRHI.h"
#include "render/DirectX/DirectXRHI.h"

#include <spdlog/spdlog.h>
#include <Eigen/Dense>

// temp
#include "render/RenderDefinition.h"

namespace RenderingDEMO
{
	Renderer::~Renderer()
	{
	}

	void Renderer::Initialize(std::shared_ptr<Window> window, RenderAPI api)
	{
		m_CurrentAPI = api;
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

		std::array<int, 2> size = window->GetWindowSize();
		m_RenderResource = std::make_shared<RenderResource>();

		m_Camera = std::make_shared<Camera>(Eigen::Vector3f(0.0f, 1.0f, 3.0f), 90.0f, static_cast<float>(size[0]) / static_cast<float>(size[1]));

		//m_WindowUI = std::make_shared<WindowUI>();
		//m_WindowUI->Initialize(window);

		PreProcess();
		SetPipline();
	}

	void Renderer::OnUpdate(float deltaTime)
	{
		/*
		Do rendering similarly as DirectX12
		Clear the color and depth buffers
			For each object in the scene :
			Transition any resources to the required state
			Bind the Pipeline State Object(PSO)
			Bind the Root Signature
			Bind any resources(CBV, UAV, SRV, Samplers, etc..) to the shader stages
			Set the primitive topology for the Input Assembler(IA)
			Bind the vertex buffer to the IA
			Bind the index buffer to the IA
			Set the viewport(s) for the Rasterizer Stage(RS)
			Set the scissor rectangle(s) for the RS
			Bind the color and depth - stencil render targets to the Output Merger(OM)
			Draw the geometry
		Present the rendered image to the screen
		*/
		UpdateConstant();
		m_RHI->ClearBackBuffer();

		// shadow pass


		// main pass
		m_RHI->SetVertexBuffer(m_RenderResource->m_CubeVertexBuffer);
		m_RHI->Draw(36);
		//m_RHI->DrawIndexed(m_RenderResource->m_CubeIndexBuffer);

		// ui pass
		//m_WindowUI->OnUpdate();



		m_RHI->SwapBuffer();
	}

	void Renderer::PreProcess()
	{
		//// anticlockwise is the default setting for OpenGL
		//// clockwise is the default setting for DirectX
		//// set DirectX rasterizer state to anticlockwise

		//cube
		//float vertices[] =
		//{
		//	//position			//color
		//	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		//	 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		//	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		//	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
		//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		//	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
		//	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		//	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f
		//};

		float vertices[] = 
		{
			//position			  //normal
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		};

		unsigned int indices[] =
		{
			//Top
			7, 6, 2,
			2, 3, 7,

			//Bottom
			0, 4, 5,
			5, 1, 0,

			//Left
			0, 2, 6,
			6, 4, 0,

			//Right
			7, 3, 1,
			1, 5, 7,

			//Front
			3, 2, 0,
			0, 1, 3,

			//Back
			4, 6, 7,
			7, 5, 4
		};

		DirectionalLight directionallight = { Eigen::Vector3f(0.0f, -0.2f, -0.2f), 0.0f, Eigen::Vector3f(1.0f, 1.0f, 1.0f), 0.0f };
		m_RenderResource->m_PerFrameConstant.DirectionalLight = directionallight;

		PointLight pointlights[] = 
		{ 
			{Eigen::Vector3f(0.0f, 2.0f, 2.0f), 0.09f, Eigen::Vector3f(1.0f, 1.0f, 1.0f), 0.032f} 
		};

		m_RenderResource->m_PerFrameConstant.PointLightNum = sizeof(pointlights) / sizeof(PointLight);
		memcpy(m_RenderResource->m_PerFrameConstant.PointLights, pointlights, sizeof(pointlights));

		//VertexElement.Name is used in DirectX to set the SemanticName. OpenGL do not need this.
		//VertexElement.Index is only used in DirectX to set the SemanticIndex
		std::vector<VertexElement> elements;
		elements.push_back({ "POSITION", 0, VertexElementType::Float3 });
		elements.push_back({ "NORMAL", 0, VertexElementType::Float3 });
		std::shared_ptr<VertexDeclaration> vd = m_RHI->CreateVertexDeclaration(elements);

		std::shared_ptr<VertexBuffer> vb = m_RHI->CreateVertexBuffer(vertices, sizeof(vertices), vd->GetStride());
		std::shared_ptr<IndexBuffer> ib = m_RHI->CreateIndexBuffer(indices, sizeof(indices));

		// temp file path
		std::shared_ptr<VertexShader> vs = m_RHI->CreateVertexShader(L"../shader/vs" + m_Suffix);
		std::shared_ptr<PixelShader> ps = m_RHI->CreatePixelShader(L"../shader/ps" + m_Suffix);

		// move to pass
		std::shared_ptr<PipelineState> pips = m_RHI->CreatePipelineState(vs, ps, vd);

		std::shared_ptr<UniformBuffer> ub = m_RHI->CreateUniformBuffer(sizeof(PerFrameConstant));

		m_RenderResource->m_CubeVertexBuffer = vb;
		m_RenderResource->m_CubeIndexBuffer = ib;
		m_RenderResource->m_CubeVertexDeclaration = vd;
		m_RenderResource->m_VertexShader = vs;
		m_RenderResource->m_PixelShader = ps;
		m_RenderResource->m_PipelineState = pips;
		m_RenderResource->m_PerFrameUniformBuffer = ub;
	}

	// move to pass
	void Renderer::SetPipline()
	{
		m_RHI->SetPipelineState(m_RenderResource->m_PipelineState);
		m_RHI->SetUniformBuffer(m_RenderResource->m_PerFrameUniformBuffer, 0);
	}

	// temp, move to render resouce
	void Renderer::UpdateConstant()
	{
		m_RenderResource->m_PerFrameConstant.CameraPos = m_Camera->GetCameraPos();
		Eigen::Matrix4f view = m_Camera->GetViewMatrix();
		Eigen::Matrix4f proj = m_Camera->GetProjectionMatrix();
		Eigen::Matrix4f projview = proj * view;
		m_RenderResource->m_PerFrameConstant.ProjectionViewMatrix = projview;

		m_RHI->UpdateUniformBuffer(m_RenderResource->m_PerFrameUniformBuffer, &m_RenderResource->m_PerFrameConstant);
	}
}