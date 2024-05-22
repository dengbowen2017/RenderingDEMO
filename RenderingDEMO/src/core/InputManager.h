#pragma once

#include "pch.h"

#include <GLFW/glfw3.h>

namespace RenderingDEMO
{
	class InputManager
	{
	public:
		InputManager() = default;
		~InputManager();

		void OnUpdate();
		void OnKey(int key, int scancode, int action, int mods);

	private:

	};
}