#include "RenderSystem.h"
#include "render/OpenGL/OpenGLRHI.h"
#include "render/DirectX/DirectXRHI.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	RenderSystem::~RenderSystem()
	{
	}

	void RenderSystem::Initialize(std::shared_ptr<Window> window, RenderAPI api)
	{
		m_CurrentAPI = api;
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
		m_Camera = std::make_shared<Camera>(GMath::Vector3(0.0f, 1.0f, 3.0f), 85.0f, static_cast<float>(size[0]) / static_cast<float>(size[1]));

		m_RenderResource = std::make_shared<RenderResource>();
		m_RenderResource->UploadTextures(m_RHI);

		m_RenderPipeline = std::make_shared<RenderPipline>();
		m_RenderPipeline->Initialize(m_RHI, m_RenderResource);
	}

	void RenderSystem::InitializeUI(std::shared_ptr<WindowUI> ui)
	{
		m_RenderPipeline->InitializeUI(ui);
	}

	void RenderSystem::SubmitMesh(std::shared_ptr<Mesh> mesh)
	{
		m_RenderResource->UploadBuffers(m_RHI, mesh);
	}

	void RenderSystem::SubmitConstant(const PerObjectConstant& constant)
	{
		m_RenderResource->UpdatePerObjectConstant(constant);
	}

	void RenderSystem::OnUpdate(float deltaTime)
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

		// BeginFrame();

		m_RenderResource->UpdatePerFrameConstant(m_Camera);
		m_RHI->UpdateUniformBuffer(m_RenderResource->m_PerFrameUniformBuffer, &m_RenderResource->m_PerFrameConstant);

		m_RHI->SetUniformBuffer(m_RenderResource->m_PerFrameUniformBuffer, 0);
		m_RHI->SetUniformBuffer(m_RenderResource->m_PerObjectUniformBuffer, 1);

		m_RenderPipeline->ForwardRendering();
		// EndFrame();
	}
}