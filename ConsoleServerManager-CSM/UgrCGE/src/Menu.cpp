#include "Menu.hpp"

namespace ugr
{
	VOID Menu::CreateMenu(Vector2i size)
	{
		this->m_size = size;
		//this->m_MiniBuffer = new CHAR_INFO[this->m_size.x * this->m_size.y];
	}
	VOID Menu::AddElements(LPCWSTR str)
	{
		this->m_vecElements.push_back(str);
	}
	VOID Menu::SetColor(SHORT color)
	{
		this->m_n16Color = color;
	}
}
