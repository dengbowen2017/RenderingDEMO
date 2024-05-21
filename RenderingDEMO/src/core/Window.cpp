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
}