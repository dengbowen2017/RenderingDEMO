#pragma once

#include "render/Camera.h"

namespace RenderingDEMO
{
    enum class EditorCommandType : unsigned int
    {
        camera_left = 1 << 0,           // A
        camera_back = 1 << 1,           // S
        camera_foward = 1 << 2,         // W
        camera_right = 1 << 3,          // D
        camera_up = 1 << 4,             // Q
        camera_down = 1 << 5,           // E
        translation_mode = 1 << 6,      // T
        rotation_mode = 1 << 7,         // R
        scale_mode = 1 << 8,            // C
        exit = 1 << 9,                  // Esc
        delete_object = 1 << 10,        // Delete
    };

	class InputManager
	{
	public:
		InputManager() = default;
		~InputManager();

        void Initialize(std::shared_ptr<Camera> camera);
		void OnUpdate(float deltaTime);

		void OnKey(int key, int scancode, int action, int mods);
        void OnCursorPos(double posX, double posY);
        void OnCursorEnter(int entered);
        void OnMouseButton(int button, int action, int mods);
        void OnWindowSize(int width, int height);

    private:
        void ProcessEditorCommand(float deltaTime);

	private:
        static const unsigned int ControlCommand = 0xFFFFFFFF;

        unsigned int m_EditorCommand = 0;

        float m_MouseX = 0.0f;
        float m_MouseY = 0.0f;
        float m_CameraSpeed = 1.0f;
        float m_MouseSpeed = 0.05f;

        bool m_IsMouseButtonRightPressed = false;
        bool m_Entered = false;

        // main camera
        std::shared_ptr<Camera> m_Camera;
	};
}