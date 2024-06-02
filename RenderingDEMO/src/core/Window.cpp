#include "Window.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::Initialize(const WindowProps& props)
	{
		if (!glfwInit())
		{
			spdlog::error("Failed to initialize GLFW");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		m_Width = props.Width;
		m_Height = props.Height;
		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title, nullptr, nullptr);
		if (!m_Window)
		{
			spdlog::error("Failed to create window");
			glfwTerminate();
			return ;
		}

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* w = (Window*)(glfwGetWindowUserPointer(window));
		if (w)
		{
			w->OnKey(key, scancode, action, mods);
		}
	}

	void Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* w = (Window*)(glfwGetWindowUserPointer(window));
		if (w)
		{
			w->m_Width = width;
			w->m_Height = height;
		}
	}

	void Window::OnKey(int key, int scancode, int action, int mods)
	{
		for (auto& f : m_OnKeyFuncs)
		{
			f(key, scancode, action, mods);
		}
	}
}