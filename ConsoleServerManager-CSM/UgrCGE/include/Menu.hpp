#pragma once
#include <Windows.h>
#include <Vector.hpp>
#include <vector>
namespace ugr
{
	class Menu
	{
	public:
		VOID CreateMenu(Vector2i size);
		VOID AddElements(LPCWSTR str);
		VOID SetColor(SHORT color);
	private:
		SHORT m_n16Color = 0x08;
		BOOL m_bIsHidden = TRUE;
		CHAR_INFO* m_MiniBuffer = nullptr;
		std::vector<LPCWSTR> m_vecElements;
		friend class Panel;
		Vector2i m_ClickableMenuPosition;
		Vector2i m_size;
	};
}