#pragma once

#include <Eigen/Dense>
#include <DirectXMath.h>

namespace RenderingDEMO
{
	struct CameraData
	{
		Eigen::Matrix4f viewprojection;
	};

	class Camera
	{
	public:
		Eigen::Matrix4f GetViewMatrix() const
		{ 
			Eigen::Matrix4f ViewMatrix;
			
			DirectX::XMFLOAT3 pos = { m_Position.x(), m_Position.y(), m_Position.z() };
			DirectX::XMVECTOR camPos = DirectX::XMLoadFloat3(&pos);
			DirectX::XMMATRIX view = DirectX::XMMatrixLookAtRH(camPos, DirectX::g_XMZero, { 0,1,0,1 });

			DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovRH(m_Fovy, m_Aspect, m_Near, m_Far);
			DirectX::XMMATRIX viewProjection = DirectX::XMMatrixMultiply(view, proj);

			DirectX::XMFLOAT4X4 matdata;
			XMStoreFloat4x4(&matdata, viewProjection);

			for (size_t i = 0; i < 4; i++)
			{
				for (size_t j = 0; j < 4; j++)
				{
					ViewMatrix(i, j) = matdata(i, j);
				}
			}

			return ViewMatrix; 
		}
		Eigen::Matrix4f GetProjectionMatrix() const
		{
			Eigen::Matrix4f ProjectionMatrix;


			return ProjectionMatrix; 
		}

	private:
		Eigen::Vector3f m_Position = { 2.0f, 2.0f, 2.0f };
		Eigen::Vector3f	m_Forward;
		float m_Yaw;
		float m_Pitch;
		
		float m_Near = 0.1f;
		float m_Far = 100.0f;
		float m_Fovy = 90.0f * 0.0174533f;
		float m_Aspect = 16.0f / 9.0f;
	};
}