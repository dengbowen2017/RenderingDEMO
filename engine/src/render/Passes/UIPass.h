#pragma once

#include "render/RenderPass.h"

#include "core/WindowUI.h"

namespace RenderingDEMO
{
	class UIPass :public RenderPass
	{
	public:
		UIPass(std::shared_ptr<WindowUI> ui)
			:m_WindowUI(ui)
		{}
		~UIPass() = default;

		virtual void Initialize() override;
		virtual void Draw() override;

	public:
		std::shared_ptr<WindowUI> m_WindowUI;
	};
}