#pragma once

#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

		//test function
		//will be removed when RenderContext is done
		void PollEventsAndClearBufferAndSetViewport();
		void SwapBuffer();

		GLFWwindow* GetWindowPointer() const { return m_Window; }
		bool WindowShouldClose() const { return glfwWindowShouldClose(m_Window); }

		typedef std::function<void(int, int, int, int)> OnKeyFunc;

		void RegisterOnKeyFunc(OnKeyFunc f) { m_OnKeyFuncs.push_back(f); }

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void OnKey(int key, int scancode, int action, int mods);

	private:
		GLFWwindow* m_Window = nullptr;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;

		std::vector<OnKeyFunc> m_OnKeyFuncs;
	};

}