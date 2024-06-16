#include "Camera.h"

#include <iostream>

namespace RenderingDEMO
{
	Camera::Camera(Eigen::Vector3f position, float fov, float aspectRatio)
		:m_Position(position), m_Fovy(fov * angle2radians), m_AspectRatio(aspectRatio)
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
		Eigen::Matrix4f viewMatrix = Eigen::Matrix4f::Zero();

		Eigen::Vector3f f = m_Forward;
		Eigen::Vector3f s = m_Right;
		Eigen::Vector3f u = m_Up;

		viewMatrix(0, 0) = s.x();
		viewMatrix(0, 1) = s.y();
		viewMatrix(0, 2) = s.z();
		viewMatrix(1, 0) = u.x();
		viewMatrix(1, 1) = u.y();
		viewMatrix(1, 2) = u.z();
		viewMatrix(2, 0) = -f.x();
		viewMatrix(2, 1) = -f.y();
		viewMatrix(2, 2) = -f.z();
		viewMatrix(0, 3) = -s.dot(m_Position);
		viewMatrix(1, 3) = -u.dot(m_Position);
		viewMatrix(2, 3) = f.dot(m_Position);
		viewMatrix(3, 3) = 1;

		return viewMatrix;
	}

	Eigen::Matrix4f Camera::GetProjectionMatrix() const
	{
		Eigen::Matrix4f projectionMatrix = Eigen::Matrix4f::Zero();

		Eigen::Array<float, 1, 1> halfFov(0.5f * m_Fovy);
		float tanFov = halfFov.sin()(0, 0);
		float h = 1.0f / tanFov;
		float w = h / m_AspectRatio;
		float f = m_Far / (m_Near - m_Far);

		projectionMatrix(0, 0) = w;
		projectionMatrix(1, 1) = h;
		projectionMatrix(2, 2) = f;
		projectionMatrix(2, 3) = f * m_Near;
		projectionMatrix(3, 2) = -1.0f;

		return projectionMatrix;
	}

	void Camera::updateCameraVectors()
	{
		Eigen::Vector3f forward;
		
		Eigen::Array<float, 1, 2> yawPitch(m_Yaw * angle2radians, m_Pitch * angle2radians);
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