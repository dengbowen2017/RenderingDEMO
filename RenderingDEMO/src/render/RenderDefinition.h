#pragma once

#include <Eigen/Dense>

#include <DirectXMath.h>

namespace RenderingDEMO
{
	struct StaticMesh
	{
		float* MeshVertices;
		unsigned int MeshVerticesSize;
		unsigned int* MeshIndices;
		unsigned int MeshIndicesSize;
	};

	struct RenderMesh
	{
		StaticMesh MeshData;
		Eigen::Matrix4f ModelMatrix;
	};

	struct DirectionalLight
	{
		Eigen::Vector3f Direction;
		float _padding1 = 0.0f;
		Eigen::Vector3f Intensity;
		float _padding2 = 0.0f;
		Eigen::Matrix4f SpaceMatrix;
	};

	struct PointLight
	{
		Eigen::Vector3f Position;
		float Quadratic; // a in shader
		Eigen::Vector3f Intensity;
		float Linear; // b in shader
	};

	struct PerFrameConstant
	{
		Eigen::Matrix4f ProjectionViewMatrix;
		Eigen::Matrix4f ProjectionViewNoTransMatirx;
		Eigen::Vector3f CameraPos;
		float _padding1 = 0.0f;
		DirectionalLight DirectionalLight;
	};

	struct PerObjectConstant
	{
		Eigen::Matrix4f ObjectModelMatrix;
	};
}