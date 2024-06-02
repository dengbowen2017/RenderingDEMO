#include "Application.h"

#include <spdlog/spdlog.h>

//temp
#include <glad/glad.h>

namespace RenderingDEMO
{
	Application::Application()
	{
		m_Window = std::make_shared<Window>();
		m_InputManager = std::make_shared<InputManager>();
		m_Renderer = std::make_shared<Renderer>();

		WindowProps props;
		m_Window->Initialize(props);
		m_Window->RegisterOnKeyFunc(std::bind(&InputManager::OnKey, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

		m_Renderer->Initialize(m_Window);
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