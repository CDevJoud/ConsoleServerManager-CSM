#pragma once
#include <Windows.h>
#include "Renderer.hpp"

namespace ugr
{
	class Panel : public Renderer
	{
	public:
		VOID CreatePanel(Vector2i size);
		VOID SetPosition(Vector2i pos);

		VOID SetBorderChar(SHORT c);
		VOID SetBorderColor(SHORT color);

		VOID AddMenuToBar(LPCWSTR title, Vector2i offset, SHORT color = 0x0F);
	private:
		friend class UgrCGE;
		SHORT m_n16BorderChar;
		SHORT m_n16BorderColor = 0x0F;
		Vector2i m_vecBufferSize;
		Vector2i m_vecPosition;
		CHAR_INFO* m_Buffer;
		RenderElements re;
	};
}