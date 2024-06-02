#pragma once

namespace RenderingDEMO
{
	



	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size)
			:m_Size(size)
		{
		}

		virtual ~VertexBuffer() = default;

		unsigned int GetSize() const { return m_Size; }

	private:
		unsigned int m_Size;
	};
}