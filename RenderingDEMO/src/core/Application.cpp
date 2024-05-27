#include "Application.h"

namespace RenderingDEMO
{
	Application::Application()
	{
		m_Window = std::make_unique<Window>();
		m_InputManager = std::make_unique<InputManager>();
		m_WindowUI = std::make_shared<WindowUI>();

		WindowProps props;
		m_Window->Initialize(props);
		m_Window->RegisterOnKeyFunc(std::bind(&InputManager::OnKey, m_InputManager.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

		m_WindowUI->Initialize(m_Window->GetWindowPointer());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (!m_Window->WindowShouldClose())
		{
			m_Window->PollEventsAndClearBufferAndSetViewport();

			m_WindowUI->ShowWindowUI();

			m_Window->SwapBuffer();
		}
	}
}