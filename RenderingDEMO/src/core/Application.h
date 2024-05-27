#pragma once

#include "pch.h"
#include "Window.h"
#include "WindowUI.h"
#include "InputManager.h"

namespace RenderingDEMO
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<InputManager> m_InputManager;
		std::shared_ptr<WindowUI> m_WindowUI;
	};
}