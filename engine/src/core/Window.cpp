#include "Window.h"

#include <spdlog/spdlog.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace RenderingDEMO
{
	Window::Window(const WindowProps& props)
	{
		if (!glfwInit())
		{
			spdlog::error("Failed to initialize GLFW");
			return;
		}

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Width = props.Width;
		m_Height = props.Height;
		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title, nullptr, nullptr);
		if (!m_Window)
		{
			spdlog::error("Failed to create window");
			glfwTerminate();
			return;
		}
		m_WindowHandler = glfwGetWin32Window(m_Window);

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetFramebufferSizeCallback(m_Window, FrameBufferSizeCallback);
		glfwSetCursorPosCallback(m_Window, CursorPosCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
	}

	Window::~Window()
	{
		glfwTerminate();
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

	void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* w = (Window*)(glfwGetWindowUserPointer(window));
		if (w)
		{
			w->OnMouseButton(button, action, mods);
		}
	}

	void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* w = (Window*)(glfwGetWindowUserPointer(window));
		if (w)
		{
			w->m_Width = width;
			w->m_Height = height;
			w->OnFrameBufferSize(width, height);
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

	void Window::OnMouseButton(int button, int action, int mods)
	{
		for (auto& f : m_OnMouseButtonFuncs)
		{
			f(button, action, mods);
		}
	}

	void Window::OnFrameBufferSize(int width, int height)
	{
		for (auto& f : m_OnFrameBufferSizeFuncs)
		{
			f(width, height);
		}
	}
}