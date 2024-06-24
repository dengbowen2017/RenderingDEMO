#pragma once

#include <Eigen/Dense>

namespace RenderingDEMO
{
	class Camera
	{
		friend class InputManager;

	public:
		Camera(Eigen::Vector3f position, float fov, float aspectRatio);
		~Camera() = default;

		void ProcessMouseMovement(float xoffset, float yoffset);

		Eigen::Matrix4f GetViewMatrix() const;
		Eigen::Matrix4f GetProjectionMatrix() const;
		Eigen::Vector3f GetCameraPos() const { return m_Position; }

	private:
		void updateCameraVectors();

	private:
		const float angle2radians = 0.0174533f;
		
		Eigen::Vector3f m_Position = {};

		Eigen::Vector3f	m_Forward = {};
		Eigen::Vector3f m_Right = {};
		Eigen::Vector3f m_Up = {};

		float m_Yaw = -90.0f;
		float m_Pitch = 0;

		float m_Near = 0.1f;
		float m_Far = 100.0f;
		float m_Fovy = 0;
		float m_AspectRatio = 0;
	};
}