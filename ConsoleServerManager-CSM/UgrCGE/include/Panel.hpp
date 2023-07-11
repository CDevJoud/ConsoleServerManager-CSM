#pragma once
#include <Windows.h>
#include "Vector.hpp"
namespace ugr
{
	class Panel
	{
	public:
		VOID CreatePanel(Vector2i size);
		VOID SetPosition(Vector2i pos);

		VOID SetBorderChar(SHORT c);
		VOID SetBorderColor(SHORT color);
	private:
		friend class UgrCGE;
		SHORT m_n16BorderChar;
		SHORT m_n16BorderColor;
		Vector2i m_vecBufferSize;
		Vector2i m_vecPosition;
		CHAR_INFO* m_Buffer;
	};
}