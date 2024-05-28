#pragma once

namespace RenderingDEMO
{
	class RenderContext
	{
	public:
		virtual void Initialize() = 0;
		virtual void SwapBuffer() = 0;
	};
}