#pragma once

#include "Window.h"
#include "WindowUI.h"
#include "InputManager.h"
#include "render/Renderer.h"

namespace RenderingDEMO
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<WindowUI> m_WindowUI;
		std::shared_ptr<InputManager> m_InputManager;
		std::shared_ptr<Renderer> m_Renderer;

		// temp
		// timing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
	};
}