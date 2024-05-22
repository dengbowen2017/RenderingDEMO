#include "Window.h"

namespace RenderingDEMO
{
	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::Initialize(const WindowProps& props)
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			spdlog::error("Failed to initialize GLFW");
			return;
		}

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
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
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
	void Window::OnKey(int key, int scancode, int action, int mods)
	{
		for (auto& f : m_OnKeyFuncs)
		{
			f(key, scancode, action, mods);
		}
	}
}