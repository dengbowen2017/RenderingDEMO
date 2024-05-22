#include "InputManager.h"

namespace RenderingDEMO
{
	InputManager::~InputManager()
	{
	}

	void InputManager::OnUpdate()
	{
	}
	void InputManager::OnKey(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			switch (key)
			{
			case GLFW_KEY_A:
				spdlog::info("A is pressed");
			default:
				break;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			switch (key)
			{
			case GLFW_KEY_A:
				spdlog::info("A is released");
			default:
				break;
			}
		}
	}
}
