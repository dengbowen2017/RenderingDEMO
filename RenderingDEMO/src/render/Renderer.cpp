#include "Renderer.h"

#include "render/OpenGL/OpenGLRHI.h"

namespace RenderingDEMO
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize(std::shared_ptr<Window> window)
	{
		m_RHI = std::make_shared<OpenGLRHI>();
		m_WindowUI = std::make_shared<WindowUI>();

		m_RHI->Initialize(window);
		m_WindowUI->Initialize(window);
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

		m_WindowUI->OnUpdate();

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
	}
}