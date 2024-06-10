#pragma once

#include "RHI.h"
#include "RenderResource.h"
#include "core/Window.h"
#include "core/WindowUI.h"


#include <d3d11.h>
#include <dxgi1_3.h>
#include <d3dcompiler.h>

#include <iostream>

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
		void OnUpdate();
		void PreProcess();
		void SetPipline();

		std::shared_ptr<RHI> GetRHI() const { return m_RHI; }

	private:
		std::shared_ptr<RHI> m_RHI;
		std::shared_ptr<WindowUI> m_WindowUI;
		std::shared_ptr<RenderResource> m_RenderResource;
	};
}