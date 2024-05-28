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

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			spdlog::error("Failed to initialize GLAD");
			return;
		}

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, KeyCallback);
	}

	void Window::OnUpdate()
	{
		
	}

	void Window::PollEventsAndClearBufferAndSetViewport()
	{
		glfwPollEvents();
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* w = (Window*)(glfwGetWindowUserPointer(window));
		if (w)
		{
			w->OnKey(key, scancode, action, mods);
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