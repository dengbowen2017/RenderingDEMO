#include "InputManager.h"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
    void InputManager::Initialize(std::shared_ptr<Camera> camera)
    {
        m_Camera = camera;
    }

    void InputManager::OnUpdate(float deltaTime)
	{
        ProcessEditorCommand(deltaTime);
	}

	void InputManager::OnKey(int key, int scancode, int action, int mods)
	{
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_A:
                m_EditorCommand |= (unsigned int)EditorCommandType::camera_left;
                break;
            case GLFW_KEY_S:
                m_EditorCommand |= (unsigned int)EditorCommandType::camera_back;
                break;
            case GLFW_KEY_W:
                m_EditorCommand |= (unsigned int)EditorCommandType::camera_foward;
                break;
            case GLFW_KEY_D:
                m_EditorCommand |= (unsigned int)EditorCommandType::camera_right;
                break;
            case GLFW_KEY_Q:
                m_EditorCommand |= (unsigned int)EditorCommandType::camera_up;
                break;
            case GLFW_KEY_E:
                m_EditorCommand |= (unsigned int)EditorCommandType::camera_down;
                break;
            case GLFW_KEY_T:
                m_EditorCommand |= (unsigned int)EditorCommandType::translation_mode;
                break;
            case GLFW_KEY_R:
                m_EditorCommand |= (unsigned int)EditorCommandType::rotation_mode;
                break;
            case GLFW_KEY_C:
                m_EditorCommand |= (unsigned int)EditorCommandType::scale_mode;
                break;
            case GLFW_KEY_DELETE:
                m_EditorCommand |= (unsigned int)EditorCommandType::delete_object;
                break;
            default:
                break;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::exit);
                break;
            case GLFW_KEY_A:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::camera_left);
                break;
            case GLFW_KEY_S:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::camera_back);
                break;
            case GLFW_KEY_W:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::camera_foward);
                break;
            case GLFW_KEY_D:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::camera_right);
                break;
            case GLFW_KEY_Q:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::camera_up);
                break;
            case GLFW_KEY_E:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::camera_down);
                break;
            case GLFW_KEY_T:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::translation_mode);
                break;
            case GLFW_KEY_R:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::rotation_mode);
                break;
            case GLFW_KEY_C:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::scale_mode);
                break;
            case GLFW_KEY_DELETE:
                m_EditorCommand &= (ControlCommand ^ (unsigned int)EditorCommandType::delete_object);
                break;
            default:
                break;
            }
        }
	}

    void InputManager::OnCursorPos(double posX, double posY)
    {
        float x = static_cast<float>(posX);
        float y = static_cast<float>(posY);

        if (m_IsMouseButtonRightPressed)
        {
            float xoffset = (x - m_MouseX) * m_Camera->m_RotationSpeed;
            float yoffset = (m_MouseY - y) * m_Camera->m_RotationSpeed; // reversed since y-coordinates go from bottom to top
            m_Camera->ProcessMouseMovement(xoffset, yoffset);
        }

        m_MouseX = x;
        m_MouseY = y;
    }

    void InputManager::OnCursorEnter(int entered)
    {
    }

    void InputManager::OnMouseButton(int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_RIGHT:
                m_IsMouseButtonRightPressed = true;
            default:
                break;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_RIGHT:
                m_IsMouseButtonRightPressed = false;
            default:
                break;
            }
        }
    }

    void InputManager::OnWindowSize(int width, int height)
    {
        assert(m_Camera != nullptr);
        m_Camera->m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
    }

    void InputManager::ProcessEditorCommand(float deltaTime)
    {
        assert(m_Camera != nullptr);

        GMath::MVector pos = GMath::LoadVector3(&m_Camera->m_Position);

        if ((unsigned int)EditorCommandType::camera_foward & m_EditorCommand)
        {
            pos += m_Camera->m_Forward * m_Camera->m_TranslationSpeed * deltaTime;
        }
        if ((unsigned int)EditorCommandType::camera_back & m_EditorCommand)
        {
            pos -= m_Camera->m_Forward * m_Camera->m_TranslationSpeed * deltaTime;
        }
        if ((unsigned int)EditorCommandType::camera_right & m_EditorCommand)
        {
            pos += m_Camera->m_Right * m_Camera->m_TranslationSpeed * deltaTime;
        }
        if ((unsigned int)EditorCommandType::camera_left & m_EditorCommand)
        {
            pos -= m_Camera->m_Right * m_Camera->m_TranslationSpeed * deltaTime;
        }
        if ((unsigned int)EditorCommandType::camera_up & m_EditorCommand)
        {
            pos += m_Camera->m_Up * m_Camera->m_TranslationSpeed * deltaTime;
        }
        if ((unsigned int)EditorCommandType::camera_down & m_EditorCommand)
        {
            pos -= m_Camera->m_Up * m_Camera->m_TranslationSpeed * deltaTime;
        }

        GMath::StoreVector3(&m_Camera->m_Position, pos);
    }
}
