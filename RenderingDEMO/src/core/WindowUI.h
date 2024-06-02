#pragma once

#include "Window.h"

namespace RenderingDEMO
{
	class WindowUI
	{
	public:
		WindowUI() = default;
		~WindowUI();

		void Initialize(std::shared_ptr<Window> window);
		void OnUpdate();

	private:
		void ShowWindowUI();

	private:
		GLFWwindow* m_Window = nullptr;

		bool m_MenuWindowOpen = true;
	};
}