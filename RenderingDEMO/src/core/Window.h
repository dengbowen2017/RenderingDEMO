#pragma once

#include <GLFW/glfw3.h>

namespace RenderingDEMO
{
	struct WindowProps
	{
		const char* Title = "RenderingDEMO";
		int Width = 1600;
		int Height = 900;
	};

	class Window
	{
	public:
		Window() = default;
		~Window();

		void Initialize(const WindowProps& props);
		void PollEvents();

		GLFWwindow* GetWindowPointer() const { return m_Window; }
		std::array<int, 2> GetWindowSize() const { return std::array<int, 2>({ m_Width, m_Height }); }
		bool WindowShouldClose() const { return glfwWindowShouldClose(m_Window); }

		typedef std::function<void(int, int, int, int)> OnKeyFunc;

		void RegisterOnKeyFunc(OnKeyFunc f) { m_OnKeyFuncs.push_back(f); }

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);

		void OnKey(int key, int scancode, int action, int mods);

	private:
		GLFWwindow* m_Window = nullptr;
		int m_Width = 0;
		int m_Height = 0;

		std::vector<OnKeyFunc> m_OnKeyFuncs;
	};

}