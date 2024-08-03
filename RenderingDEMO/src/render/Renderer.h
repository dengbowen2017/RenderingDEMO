#pragma once

#include "RHI.h"
#include "RenderResource.h"
#include "RenderPipline.h"
#include "core/Window.h"
#include "Camera.h"

namespace RenderingDEMO
{
	class WindowUI;

	enum class RenderAPI : unsigned int
	{
		Unknown = 0, OpenGL, DirectX
	};

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer();

		void Initialize(std::shared_ptr<Window> window, RenderAPI api);
		void InitializeUI(std::shared_ptr<WindowUI> ui);
		void OnUpdate(float deltaTime);

		std::shared_ptr<RHI> GetRHI() const { return m_RHI; }
		std::shared_ptr<Camera> GetMainCamera() const { return m_Camera; }

	private:
		std::shared_ptr<RHI> m_RHI;
		std::shared_ptr<RenderPipline> m_RenderPipeline;
		std::shared_ptr<RenderResource> m_RenderResource;

		// temp
		std::shared_ptr<Camera> m_Camera;

		RenderAPI m_CurrentAPI = RenderAPI::Unknown;
	};
}