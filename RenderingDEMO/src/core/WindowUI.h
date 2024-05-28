#pragma once

#include <GLFW/glfw3.h>

namespace RenderingDEMO
{
	class WindowUI
	{
	public:
		WindowUI(GLFWwindow* window);
		~WindowUI();

		void Initialize();
		void ShowWindowUI();
		void OnUpdate();

	private:
		GLFWwindow* m_Window = nullptr;

		bool m_MenuWindowOpen = true;
	};
}