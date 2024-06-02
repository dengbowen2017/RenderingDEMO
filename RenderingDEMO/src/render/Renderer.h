#pragma once

#include "RHI.h"
#include "core/Window.h"
#include "core/WindowUI.h"

namespace RenderingDEMO
{
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer();

		void Initialize(std::shared_ptr<Window> window);

		void OnUpdate();

		void ProcessMeshData();

	private:
		std::shared_ptr<RHI> m_RHI;
		std::shared_ptr<WindowUI> m_WindowUI;

		//std::shared_ptr<RenderResource> 
		//std::shared_ptr<ShaderState>
		//std::shared_ptr<RenderPipline>
		//std::shared_ptr<RenderCamera>
	};
}