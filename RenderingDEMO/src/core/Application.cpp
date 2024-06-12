#include "Application.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	Application::Application()
	{
		m_Window = std::make_shared<Window>();
		m_InputManager = std::make_shared<InputManager>();
		m_Renderer = std::make_shared<Renderer>();

		// Initialize GLFWwindow
		WindowProps props;
		m_Window->Initialize(props);
		m_Window->RegisterOnKeyFunc(std::bind(&InputManager::OnKey, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

		// TODO: Pass render information from main
		// temp: Set API here
		m_Renderer->Initialize(m_Window, RenderAPI::OpenGL);
		m_Window->RegisterOnWindowSizeFunc(std::bind(&RHI::RecreateSwapChain, m_Renderer->GetRHI().get(), std::placeholders::_1, std::placeholders::_2));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (!m_Window->WindowShouldClose())
		{
			m_Window->PollEvents();

			m_InputManager->OnUpdate();
			
			m_Renderer->OnUpdate();
		}
	}
}