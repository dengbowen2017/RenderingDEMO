#include "Camera.h"

#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
	Camera::Camera(GMath::Vector3 position, float fov, float aspectRatio)
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

	GMath::MMatrix Camera::GetViewMat() const
	{
		GMath::MVector EyePos = GMath::LoadVector3(&m_Position);
		return GMath::MatrixLookAtRH(EyePos, EyePos + m_Forward, m_WorldUp);
	}

	GMath::MMatrix Camera::GetProjectionMat() const
	{
		return GMath::MatrixPerspectiveFovRH(GMath::ConvertToRadians(m_Fovy), m_AspectRatio, m_Near, m_Far);
	}

	void Camera::updateCameraVectors()
	{
		float sinYaw = GMath::ScalarSin(GMath::ConvertToRadians(m_Yaw));
		float cosYaw = GMath::ScalarCos(GMath::ConvertToRadians(m_Yaw));

		float sinPitch = GMath::ScalarSin(GMath::ConvertToRadians(m_Pitch));
		float cosPitch = GMath::ScalarCos(GMath::ConvertToRadians(m_Pitch));

		GMath::MVector temp(cosYaw * cosPitch, sinPitch, sinYaw * cosPitch, 0);

		m_Forward = GMath::VectorNormalize(temp);
		m_Right = GMath::VectorNormalize(GMath::VectorCross(m_Forward, m_WorldUp));
		m_Up = GMath::VectorNormalize(GMath::VectorCross(m_Right, m_Forward));
	}
}