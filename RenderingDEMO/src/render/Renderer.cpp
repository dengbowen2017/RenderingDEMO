#include "Renderer.h"

#include "render/OpenGL/OpenGLRHI.h"


// temp
#include <glad/glad.h>

namespace RenderingDEMO
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize(std::shared_ptr<Window> window)
	{
		m_RHI = std::make_shared<OpenGLRHI>();
		//m_WindowUI = std::make_shared<WindowUI>();

		m_RHI->Initialize(window);
		//m_WindowUI->Initialize(window);

		ProcessMeshData();
	}

	void Renderer::OnUpdate()
	{
		// need a pipline to specify which type of rendering we need
		// for now we only have forward rendering so we don't need pipline
		
		// forward rendering
		// just render a triangle 
		// clear framebuffer
		// set render resource
		// set shader
		// draw 
		// swap buffer

		m_RHI->ClearBackBuffer(0.2f, 0.3f, 0.7f, 1.0f);

		//m_WindowUI->OnUpdate();

		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		m_RHI->Draw(m_IndexBuffer->GetCount());

		m_RHI->SwapBuffer();
	}

	void Renderer::ProcessMeshData()
	{
		// need a asset manager to manage all the raw mesh and texture data
		// and then create render buffer from asset manager 
		// now we hard code mesh data here and upload data to render buffer

		// all the render buffer is stored in the RenderResource
		// whether in ID3DBuffer* or Guint


		// create shader and shader layout according to mesh data layout
		// maybe we need a new function SetupRenderingContext to create shader and set shader layout

		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer = m_RHI->CreateVertexBuffer(vertices, sizeof(vertices));
		m_RHI->SetVertexBuffer(m_VertexBuffer);

		std::vector<VertexElement> elements;
		elements.push_back({ "Position", VertexElementType::Float3 });

		m_VertexDeclaration = m_RHI->CreateVertexDeclaration(elements);
		m_RHI->SetShaderState(m_VertexDeclaration);

		unsigned int indices[3] =
		{
			0, 1, 2
		};

		m_IndexBuffer = m_RHI->CreateIndexBuffer(indices, sizeof(indices));
		m_RHI->SetIndexBuffer(m_IndexBuffer);
	}
}