#include "Window.h"

#include <spdlog/spdlog.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

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

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		m_Width = props.Width;
		m_Height = props.Height;
		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title, nullptr, nullptr);
		if (!m_Window)
		{
			spdlog::error("Failed to create window");
			glfwTerminate();
			return ;
		}

		m_WindowHandler = glfwGetWin32Window(m_Window);

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
		glfwSetCursorPosCallback(m_Window, CursorPosCallback);
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

	void Window::CursorPosCallback(GLFWwindow* window, double posX, double posY)
	{
		Window* w = (Window*)(glfwGetWindowUserPointer(window));
		if (w)
		{
			w->OnCursorPos(posX, posY);
		}
	}

	void Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* w = (Window*)(glfwGetWindowUserPointer(window));
		if (w)
		{
			w->m_Width = width;
			w->m_Height = height;
			w->OnWindowSize(width, height);
		}
	}

	void Window::OnKey(int key, int scancode, int action, int mods)
	{
		for (auto& f : m_OnKeyFuncs)
		{
			f(key, scancode, action, mods);
		}
	}

	void Window::OnCursorPos(double posX, double posY)
	{
		for (auto& f : m_OnCursorPosFuncs)
		{
			f(posX, posY);
		}
	}

	void Window::OnWindowSize(int width, int height)
	{
		for (auto& f : m_OnWindowSizeFuncs)
		{
			f(width, height);
		}
	}
}