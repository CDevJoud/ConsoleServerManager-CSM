#pragma once
#include <Windows.h>
#include <Vector.hpp>
#include <vector>
#include <string>
#include <EventProcessor.hpp>
namespace ugr
{
	class TextBox
	{
	public:
		VOID CreateBox(Vector2i size);
		VOID SetPosition(Vector2i pos);
		VOID AddLine(LPCWSTR str);
		VOID SetTextBoxColor(SHORT color);
		INT GetScrollPosition() const { return this->m_nScrollPosition; }
		VOID MoveUp() { this->m_nScrollPosition--; }
		VOID MoveDown() { this->m_nScrollPosition++; }
		INT GetLinesSize() const { return m_vecLines.size(); }
	private:
		friend class Panel;
		Vector2i m_size;
		CHAR_INFO* m_Buffer;
		Vector2i m_pos;

		std::vector<std::wstring> m_vecLines;
		int m_nVisibleHeight; // Height of the visible region
		int m_nScrollPosition = 0; // Current scroll position
		SHORT m_n16Color = 0x00;


		Vector2i m_scrollbarPosition;
		int m_nScrollBarHeight;
	};
}