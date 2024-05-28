#pragma once

#include "render/RenderContext.h"

#include <GLFW/glfw3.h>

namespace RenderingDEMO
{
	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		~OpenGLContext();

		virtual void Initialize() override;
		virtual void SwapBuffer() override;

	private:
		GLFWwindow* m_Window;
	};
}