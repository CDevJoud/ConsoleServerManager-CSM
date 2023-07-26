#include <TextBox.hpp>

namespace ugr
{
	VOID TextBox::CreateBox(Vector2i size)
	{
		this->m_size = size;
		this->m_scrollbarPosition.x = size.x - 2;
		this->m_scrollbarPosition.y = 1;
		this->m_nScrollBarHeight = size.y - 2;
		this->m_nVisibleHeight = size.y;
	}
	VOID TextBox::SetPosition(Vector2i pos)
	{
		this->m_pos = pos;
	}
	VOID TextBox::AddLine(LPCWSTR str)
	{
		this->m_vecLines.push_back(str);
	}
	VOID TextBox::SetTextBoxColor(SHORT color)
	{
		this->m_n16Color = color;
	}
}