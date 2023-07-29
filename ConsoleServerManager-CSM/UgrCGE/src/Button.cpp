#include "Button.hpp"

namespace ugr
{
	VOID Button::SetTitle(LPCWSTR t, BYTE col)
	{
		this->m_title = t;
		this->m_n8TitleColor = col;
		this->m_size.x = lstrlenW(t) + 2;
	}
	VOID Button::SetColor(BYTE color)
	{
		this->m_n8Color = color;
	}
	VOID Button::SetPosition(Vector2i pos)
	{
		this->m_pos = pos;
	}
	VOID Button::ProcessEvents(EventProcessor* EP)
	{
		auto mousePos = EP->GetMousePos();
		INT y1 = mousePos.y - 1;
		INT y2 = m_posRelativeToConsole.y - 1;
		//Check for hovering
		if (mousePos.x >= this->m_posRelativeToConsole.x && mousePos.x <= (this->m_posRelativeToConsole.x + this->m_size.x) - 1 && y1 == y2)
		{
			//check for click
			if (EP->Mouse(EventProcessor::MouseType::Left).bStrokePressed)
			{
				this->m_bIsClicked = TRUE;
				return;
			}
			else
				this->m_bIsClicked = FALSE;
			this->m_bIsHovering = TRUE;
		}
		else
			this->m_bIsHovering = FALSE;
	}
	BOOL Button::IsClicked()
	{
		return this->m_bIsClicked;
	}
	BOOL Button::IsHovering()
	{
		return this->m_bIsHovering;
	}
}