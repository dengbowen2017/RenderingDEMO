#pragma once

#include "GMathLib.h"

namespace RenderingDEMO
{
	class Camera
	{
		friend class InputManager;

	public:
		Camera(GMath::Vector3 position, float fov, float aspectRatio);
		~Camera() = default;

		void ProcessMouseMovement(float xoffset, float yoffset);

		GMath::MMatrix GetViewMat() const;
		GMath::MMatrix GetProjectionMat() const;

		GMath::Vector3 GetCameraPos() const { return m_Position; }

	private:
		void updateCameraVectors();

	private:
		GMath::Vector3 m_Position = {};

		GMath::MVector m_Forward = {};
		GMath::MVector m_Right = {};
		GMath::MVector m_Up = {};

		float m_Fovy = 0;
		float m_AspectRatio = 0;

		// TODO: set at constructor
		GMath::MVector m_WorldUp = { 0.0f, 1.0f, 0.0f, 0.0f }; 
		float m_Yaw = -90.0f;
		float m_Pitch = 0;
		float m_Near = 0.1f;
		float m_Far = 100.0f;		
		float m_RotationSpeed = 0.04f;
		float m_TranslationSpeed = 1.5f;
	};
}