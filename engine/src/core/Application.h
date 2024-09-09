#pragma once

#include "Window.h"
#include "WindowUI.h"
#include "InputManager.h"
#include "render/RenderSystem.h"
#include "physics/PhysicsSystem.h"
#include "scene/SceneSystem.h"

namespace RenderingDEMO
{
	class Application
	{
	public:
		Application();
		~Application() = default;

		void Run();

	private:
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<WindowUI> m_WindowUI;
		std::shared_ptr<InputManager> m_InputManager;
		std::shared_ptr<RenderSystem> m_RenderSystem;
		std::shared_ptr<PhysicsDEMO::PhysicsSystem> m_PhysicsSystem;
		std::shared_ptr<SceneSystem> m_SceneSystem;

		// temp
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
	};
}