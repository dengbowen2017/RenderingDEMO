#include "OpenGLContext.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h>

namespace RenderingDEMO
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_Window(window)
	{

	}

	OpenGLContext::~OpenGLContext()
	{

	}

	void OpenGLContext::Initialize()
	{
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			spdlog::error("Failed to initialize GLAD");
			return;
		}
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}
}