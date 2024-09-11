#include "Application.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	Application::Application()
	{
		m_Window = std::make_shared<Window>();
		m_InputManager = std::make_shared<InputManager>();
		m_RenderSystem = std::make_shared<RenderSystem>();
		m_PhysicsSystem = std::make_shared<PhysicsDEMO::PhysicsSystem>();
		m_SceneSystem = std::make_shared<SceneSystem>();

		WindowProps props;
		m_Window->Initialize(props);

		// TODO: Pass render information from main
		// temp: Set API here
		m_RenderSystem->Initialize(m_Window, RenderAPI::OpenGL);
		
		m_InputManager->Initialize(m_RenderSystem->GetMainCamera());

		m_PhysicsSystem->Initialize(PhysicsDEMO::PhysicsSystemType::Default);

		m_SceneSystem->Initialize(m_RenderSystem, m_PhysicsSystem);

		m_Window->RegisterOnKeyFunc(std::bind(&InputManager::OnKey, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		m_Window->RegisterOnCursorPosFunc(std::bind(&InputManager::OnCursorPos, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2));
		m_Window->RegisterOnMouseButtonFunc(std::bind(&InputManager::OnMouseButton, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		m_Window->RegisterOnFrameBufferSizeFunc(std::bind(&RHI::RecreateSwapChain, m_RenderSystem->GetRHI().get(), std::placeholders::_1, std::placeholders::_2));
		m_Window->RegisterOnFrameBufferSizeFunc(std::bind(&InputManager::OnWindowSize, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2));
	}

	void Application::Run()
	{
		while (!m_Window->WindowShouldClose())
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			spdlog::info("{0} FPS", 1 / deltaTime);

			m_Window->PollEvents();
			m_InputManager->OnUpdate(deltaTime);
			m_SceneSystem->OnUpdate(deltaTime);
			m_RenderSystem->OnUpdate(deltaTime);
		}
	}
}