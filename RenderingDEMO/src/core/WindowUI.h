#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace RenderingDEMO
{
	class WindowUI
	{
	public:
		WindowUI() = default;
		~WindowUI();

		void Initialize(GLFWwindow* window);
		void ShowWindowUI();
		void OnUpdate();

	private:
		GLFWwindow* m_Window = nullptr;

		bool m_MenuWindowOpen = true;
	};
}