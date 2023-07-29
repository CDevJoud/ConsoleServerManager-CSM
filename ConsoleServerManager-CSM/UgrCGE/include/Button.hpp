#pragma once
#include <EventProcessor.hpp>
#include <Vector.hpp>
#include <string>
namespace ugr
{
	class Button
	{
	public:
		VOID SetTitle(LPCWSTR title, BYTE color);
		VOID SetColor(BYTE color);
		VOID SetPosition(Vector2i pos);
		VOID ProcessEvents(EventProcessor* EP);
		BOOL IsClicked();
		BOOL IsHovering();
	private:
		friend class Panel;
		Vector2i m_size;
		LPCWSTR m_title;
		BYTE m_n8TitleColor;
		BYTE m_n8Color;
		Vector2i m_pos;
		Vector2i m_posRelativeToConsole;
		BOOL m_bIsClicked;
		BOOL m_bIsHovering;
	};
}