#pragma once

#include <GLFW/glfw3.h>

namespace RenderingDEMO
{
	struct WindowProps
	{
		const char* Title = "RenderingDEMO";
		int Width = 1600;
		int Height = 900;
	};

	class Window
	{
	public:
		Window() = default;
		~Window();

		void Initialize(const WindowProps& props);
		void PollEvents();

		GLFWwindow* GetWindowPointer() const { return m_Window; }
		std::array<int, 2> GetWindowSize() const { return std::array<int, 2>({ m_Width, m_Height }); }
		HWND GetWindowHandler() const { return m_WindowHandler; }
		bool WindowShouldClose() const { return glfwWindowShouldClose(m_Window); }

		typedef std::function<void(int, int, int, int)>		OnKeyFunc;
		typedef std::function<void(double, double)>			OnCursorPosFunc;
		typedef std::function<void(int, int, int)>			OnMouseButtonFunc;
		typedef std::function<void(int, int)>				OnFrameBufferSizeFunc;

		void RegisterOnKeyFunc(OnKeyFunc f) { m_OnKeyFuncs.push_back(f); }
		void RegisterOnCursorPosFunc(OnCursorPosFunc f) { m_OnCursorPosFuncs.push_back(f); }
		void RegisterOnMouseButtonFunc(OnMouseButtonFunc f) { m_OnMouseButtonFuncs.push_back(f); }
		void RegisterOnFrameBufferSizeFunc(OnFrameBufferSizeFunc f) { m_OnFrameBufferSizeFuncs.push_back(f); }

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CursorPosCallback(GLFWwindow* window, double posX, double posY);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

		void OnKey(int key, int scancode, int action, int mods);
		void OnCursorPos(double posX, double posY);
		void OnMouseButton(int button, int action, int mods);
		void OnFrameBufferSize(int width, int height);

	private:
		HWND m_WindowHandler = nullptr;
		GLFWwindow* m_Window = nullptr;
		int m_Width = 0;
		int m_Height = 0;

		std::vector<OnKeyFunc> m_OnKeyFuncs;
		std::vector<OnCursorPosFunc> m_OnCursorPosFuncs;
		std::vector<OnMouseButtonFunc> m_OnMouseButtonFuncs;
		std::vector<OnFrameBufferSizeFunc> m_OnFrameBufferSizeFuncs;
	};

}