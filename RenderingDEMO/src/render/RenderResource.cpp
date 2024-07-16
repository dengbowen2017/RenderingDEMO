#include "RenderResource.h"

#include "RenderUtil.h"

#include <DirectXMath.h>

namespace RenderingDEMO
{
    void RenderResource::UpdatePerFrameConstant(std::shared_ptr<Camera> camera)
    {
        m_PerFrameConstant.CameraPos = camera->GetCameraPos();
        m_PerFrameConstant.ProjectionViewMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();
    }

    void RenderResource::UpdateBuffers(std::shared_ptr<RHI> rhi)
    {
		float cubeVertices[] =
		{
			//position			  //normal
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		};

		float planeVertices[] =
		{
			 20.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f,
			 20.0f, -1.0f,  20.0f, 0.0f, 1.0f, 0.0f,
			-20.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f,
			-20.0f, -1.0f,  20.0f, 0.0f, 1.0f, 0.0f
		};

		unsigned int planeIndices[] =
		{
			0, 3, 1,
			2, 3, 0
		};

		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		unsigned int quadIndices[] =
		{
			0, 1, 2,
			2, 1, 3
		};

		unsigned int stride = 24; // Float3 * 2
		std::shared_ptr<VertexBuffer> vb = rhi->CreateVertexBuffer(cubeVertices, sizeof(cubeVertices), stride);
		m_CubeVertexBuffer = vb;

		vb = rhi->CreateVertexBuffer(planeVertices, sizeof(planeVertices), stride);
		std::shared_ptr<IndexBuffer> ib = rhi->CreateIndexBuffer(planeIndices, sizeof(planeIndices));
		m_PlaneVertexBuffer = vb;
		m_PlaneIndexBuffer = ib;

		stride = 20;
		vb = rhi->CreateVertexBuffer(quadVertices, sizeof(quadVertices), stride);
		ib = rhi->CreateIndexBuffer(quadIndices, sizeof(quadIndices));
		m_QuadVertexBuffer = vb;
		m_QuadIndexBuffer = ib;

		// directional light looking at world zero
		Eigen::Vector3f lightPos(-2.0f, 4.0f, -1.0f);
		Eigen::Matrix4f view = Math::GetLookAtMatrix(lightPos, Eigen::Vector3f::Zero(), Eigen::Vector3f(0.0f, 1.0f, 0.0f));
		Eigen::Matrix4f proj = Math::GetOrthographicMatrix(20, 20, 1.0f, 7.5f);
		Eigen::Matrix4f lightSpaceMat = proj * view;

		DirectionalLight directionallight = { -lightPos, 0.0f, Eigen::Vector3f(1.0f, 1.0f, 1.0f), 0.0f, lightSpaceMat };
		m_PerFrameConstant.DirectionalLight = directionallight;

		//PointLight pointlights[] =
		//{
		//	{Eigen::Vector3f(0.0f, 2.0f, 2.0f), 0.09f, Eigen::Vector3f(1.0f, 1.0f, 1.0f), 0.032f}
		//};
		//m_PerFrameConstant.PointLightNum = sizeof(pointlights) / sizeof(PointLight);
		//memcpy(m_PerFrameConstant.PointLights, pointlights, sizeof(pointlights));

		std::shared_ptr<UniformBuffer> ub = rhi->CreateUniformBuffer(sizeof(PerFrameConstant));
		m_PerFrameUniformBuffer = ub;
    }
}