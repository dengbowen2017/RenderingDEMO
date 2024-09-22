#pragma once

#include "RHI.h"
#include "RenderResource.h"
#include "RenderPipline.h"
#include "core/Window.h"
#include "Camera.h"

namespace RenderingDEMO
{
	class WindowUI;
	struct Mesh;

	enum class RenderAPI : unsigned int
	{
		Unknown = 0, OpenGL, DirectX
	};

	class RenderSystem
	{
	public:
		RenderSystem(std::shared_ptr<Window> window, RenderAPI api);
		~RenderSystem();

		void Initialize(std::shared_ptr<Window> window, RenderAPI api);
		void InitializeUI(std::shared_ptr<WindowUI> ui);
		void OnUpdate(float deltaTime);

		void SubmitMesh(std::shared_ptr<Mesh> mesh);
		void SubmitConstants(const std::vector<PerObjectConstant>& constants);

		void SetSceneCamera(std::shared_ptr<Camera> camera);

		std::shared_ptr<RHI> GetRHI() const { return m_RHI; }

	private:
		std::shared_ptr<RHI> m_RHI;
		std::shared_ptr<RenderPipline> m_RenderPipeline;
		std::shared_ptr<RenderResource> m_RenderResource;

		// temp
		std::shared_ptr<Camera> m_Camera;

		RenderAPI m_CurrentAPI = RenderAPI::Unknown;
	};
}