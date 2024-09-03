#pragma once

#include "Window.h"

namespace RenderingDEMO
{
	class WindowUI
	{
	public:
		~WindowUI();

		void Initialize(std::shared_ptr<Window> window);
		void Draw();

	private:
		void ShowWindowUI();

	private:
		GLFWwindow* m_Window = nullptr;

		bool m_MenuWindowOpen = true;
	};
}