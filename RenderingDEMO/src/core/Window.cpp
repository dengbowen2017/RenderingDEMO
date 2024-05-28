#include "Window.h"
#include "render/OpenGL/OpenGLContext.h"

#include <spdlog/spdlog.h>

//should not be included here
#include <glad/glad.h>

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

		m_RenderContext = std::make_unique<OpenGLContext>(m_Window);
		m_RenderContext->Initialize();

		m_WindowUI = std::make_unique<WindowUI>(m_Window);
		m_WindowUI->Initialize();
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window, &display_w, &display_h);

		//will be moved to render
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_WindowUI->ShowWindowUI();

		m_RenderContext->SwapBuffer();
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