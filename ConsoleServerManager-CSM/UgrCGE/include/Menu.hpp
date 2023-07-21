#pragma once
#include <Windows.h>
#include <Vector.hpp>
namespace ugr
{
	class Menu
	{
	public:
		VOID CreateMenu(Vector2i size);
	private:
		friend class Panel;
		Vector2i m_ClickableMenuPosition;

	};
}