#include "RenderResource.h"

namespace RenderingDEMO
{
    void RenderResource::UpdatePerFrameConstant(std::shared_ptr<Camera> camera)
    {
        m_PerFrameConstant.CameraPos = camera->GetCameraPos();
        m_PerFrameConstant.ProjectionViewMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();
    }

    void RenderResource::UpdateBuffers(std::shared_ptr<RHI> rhi)
    {
		float vertices[] =
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

		unsigned int indices[] =
		{
			//Top
			7, 6, 2,
			2, 3, 7,

			//Bottom
			0, 4, 5,
			5, 1, 0,

			//Left
			0, 2, 6,
			6, 4, 0,

			//Right
			7, 3, 1,
			1, 5, 7,

			//Front
			3, 2, 0,
			0, 1, 3,

			//Back
			4, 6, 7,
			7, 5, 4
		};

		DirectionalLight directionallight = { Eigen::Vector3f(-0.1f, -0.2f, -0.2f), 0.0f, Eigen::Vector3f(1.0f, 1.0f, 1.0f), 0.0f };
		m_PerFrameConstant.DirectionalLight = directionallight;

		PointLight pointlights[] =
		{
			{Eigen::Vector3f(0.0f, 2.0f, 2.0f), 0.09f, Eigen::Vector3f(1.0f, 1.0f, 1.0f), 0.032f}
		};

		m_PerFrameConstant.PointLightNum = sizeof(pointlights) / sizeof(PointLight);
		memcpy(m_PerFrameConstant.PointLights, pointlights, sizeof(pointlights));

		std::vector<VertexElement> elements;
		elements.push_back({ "POSITION", 0, VertexElementType::Float3 });
		elements.push_back({ "NORMAL", 0, VertexElementType::Float3 });
		std::shared_ptr<VertexDeclaration> vd = rhi->CreateVertexDeclaration(elements);

		std::shared_ptr<VertexBuffer> vb = rhi->CreateVertexBuffer(vertices, sizeof(vertices), vd->GetStride());
		std::shared_ptr<IndexBuffer> ib = rhi->CreateIndexBuffer(indices, sizeof(indices));
		std::shared_ptr<UniformBuffer> ub = rhi->CreateUniformBuffer(sizeof(PerFrameConstant));

		m_CubeVertexBuffer = vb;
		m_CubeIndexBuffer = ib;
		m_PerFrameUniformBuffer = ub;
		m_VertexDeclaration = vd;
    }
}