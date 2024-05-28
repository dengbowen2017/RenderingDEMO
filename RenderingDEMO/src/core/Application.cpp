#include "Application.h"

namespace RenderingDEMO
{
	Application::Application()
	{
		m_Window = std::make_unique<Window>();
		m_InputManager = std::make_unique<InputManager>();

		WindowProps props;
		m_Window->Initialize(props);
		m_Window->RegisterOnKeyFunc(std::bind(&InputManager::OnKey, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (!m_Window->WindowShouldClose())
		{
			m_InputManager->OnUpdate();
			m_Window->OnUpdate();
		}
	}
}