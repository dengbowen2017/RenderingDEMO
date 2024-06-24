#pragma once

#include <Eigen/Dense>

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
		float _padding1;
		Eigen::Vector3f Intensity;
		float _padding2;
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
		Eigen::Vector3f CameraPos;
		uint32_t PointLightNum;
		PointLight PointLights[8]; // temp, max to 8
		DirectionalLight DirectionalLight;
	};

	struct PerObjectConstant
	{
		Eigen::Matrix4f ObjectModelMatrix;
	};
}