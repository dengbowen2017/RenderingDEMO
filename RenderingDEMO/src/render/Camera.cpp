#include "Camera.h"

#include <spdlog/spdlog.h>
#include "RenderUtil.h"

namespace RenderingDEMO
{
	Camera::Camera(Eigen::Vector3f position, float fov, float aspectRatio)
		:m_Position(position), m_Fovy(fov), m_AspectRatio(aspectRatio)
	{
		updateCameraVectors();
	}

	void Camera::ProcessMouseMovement(float xoffset, float yoffset)
	{
		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (m_Pitch > 89.0f)
		{
			m_Pitch = 89.0f;
		}
		if (m_Pitch < -89.0f)
		{
			m_Pitch = -89.0f;
		}
		updateCameraVectors();
	}

	Eigen::Matrix4f Camera::GetViewMatrix() const
	{
		return Math::GetLookAtMatrix(m_Position, m_Position + m_Forward, { 0.0f, 1.0f, 0.0f });
	}

	Eigen::Matrix4f Camera::GetProjectionMatrix() const
	{
		return Math::GetPerspectiveFovMatrix(m_Fovy, m_AspectRatio, m_Near, m_Far);
	}

	void Camera::updateCameraVectors()
	{
		Eigen::Vector3f forward;
		
		Eigen::Array<float, 1, 2> yawPitch(m_Yaw * 0.0174533f, m_Pitch * 0.0174533f);
		Eigen::Array<float, 1, 2> sinValue = yawPitch.sin();
		Eigen::Array<float, 1, 2> cosValue = yawPitch.cos();

		forward(0) = cosValue(0, 0) * cosValue(0, 1);
		forward(1) = sinValue(0, 1);
		forward(2) = sinValue(0, 0) * cosValue(0, 1);

		Eigen::Vector3f worldUp(0.0f, 1.0f, 0.0f);
		m_Forward = forward.normalized();
		m_Right = m_Forward.cross(worldUp).normalized();
		m_Up = m_Right.cross(m_Forward).normalized();
	}
}