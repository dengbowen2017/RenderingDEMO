#pragma once

#include "RHI.h"
#include "RenderResource.h"
#include "RenderPipline.h"
#include "core/Window.h"
#include "core/WindowUI.h"
#include "Camera.h"

namespace RenderingDEMO
{
	enum RenderAPI
	{
		Unknown = 0, OpenGL, DirectX
	};

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer();

		void Initialize(std::shared_ptr<Window> window, RenderAPI api);
		void OnUpdate(float deltaTime);

		std::shared_ptr<RHI> GetRHI() const { return m_RHI; }
		std::shared_ptr<Camera> GetMainCamera() const { return m_Camera; }

	private:
		std::shared_ptr<RHI> m_RHI;
		std::shared_ptr<WindowUI> m_WindowUI;
		std::shared_ptr<RenderResource> m_RenderResource;
		std::shared_ptr<RenderPipline> m_RenderPipeline;
		std::shared_ptr<Camera> m_Camera;

		RenderAPI m_CurrentAPI = RenderAPI::Unknown;
	};
}