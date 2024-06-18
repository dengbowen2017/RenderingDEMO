#include "Application.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	Application::Application()
	{
		m_Window = std::make_shared<Window>();
		m_InputManager = std::make_shared<InputManager>();
		m_Renderer = std::make_shared<Renderer>();

		WindowProps props;
		m_Window->Initialize(props);
		// TODO: Pass render information from main
		// temp: Set API here
		m_Renderer->Initialize(m_Window, RenderAPI::OpenGL);
		m_InputManager->Initialize(m_Renderer->GetMainCamera());

		m_Window->RegisterOnKeyFunc(std::bind(&InputManager::OnKey, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		m_Window->RegisterOnCursorPosFunc(std::bind(&InputManager::OnCursorPos, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2));
		m_Window->RegisterOnMouseButtonFunc(std::bind(&InputManager::OnMouseButton, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		m_Window->RegisterOnFrameBufferSizeFunc(std::bind(&RHI::RecreateSwapChain, m_Renderer->GetRHI().get(), std::placeholders::_1, std::placeholders::_2));
		m_Window->RegisterOnFrameBufferSizeFunc(std::bind(&InputManager::OnWindowSize, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (!m_Window->WindowShouldClose())
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			m_Window->PollEvents();
			m_InputManager->OnUpdate(deltaTime);
			m_Renderer->OnUpdate(deltaTime);
		}
	}
}