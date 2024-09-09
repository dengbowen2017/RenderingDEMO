#pragma once

#include "GMath.h"

namespace RenderingDEMO
{
	//struct PointLight
	//{
	//	Eigen::Vector3f Position;
	//	float Quadratic; // a in shader
	//	Eigen::Vector3f Intensity;
	//	float Linear; // b in shader
	//};

	struct DirectionalLight
	{
		GMath::Vector3 Direction;
		float _padding1 = 0.0f;
		GMath::Vector3 Intensity;
		float _padding2 = 0.0f;
		GMath::Matrix4x4 SpaceMatrix;
	};

	struct PerFrameConstant
	{
		GMath::Matrix4x4 ProjectionViewMatrix;
		GMath::Matrix4x4 ProjectionViewNoTransMatrix;
		GMath::Vector3 CameraPos;
		float _padding1 = 0.0f;
		DirectionalLight DirectionalLight;
	};

	struct PerObjectConstant
	{
		GMath::Matrix4x4 ModelMatrix;
	};
}