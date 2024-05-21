#pragma once

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	struct WindowProps
	{
		const char* Title = "RenderingDEMO";
		uint32_t Width = 1600;
		uint32_t Height = 900;
	};

	class Window
	{
	public:
		Window() = default;
		~Window();

		void Initialize(const WindowProps& props);
		void OnUpdate();

		GLFWwindow* GetWindowPointer() const { return m_Window; }
		bool WindowShouldClose() const { return glfwWindowShouldClose(m_Window); }

	private:
		GLFWwindow* m_Window = nullptr;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
	};

}