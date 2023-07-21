#pragma once
#include <Windows.h>
#include <Renderer.hpp>
#include <Menu.hpp>
#include <unordered_map>
#include <EventProcessor.hpp>
#include <string>
namespace ugr
{
	class Panel : public Renderer
	{
	public:
		VOID CreatePanel(Vector2i size);
		VOID SetPosition(Vector2i pos);

		VOID SetBorderChar(SHORT c);
		VOID SetBorderColor(SHORT color);

		VOID CreateMenuBar(BYTE sizex, SHORT c, SHORT color);
		VOID AddMenu(LPCWSTR menutitle, Menu* attachMenuto, SHORT color);

		//DANGEROUS FUNCTION
		//VOID RenderPanel(Panel* p);

		VOID SetTitle(LPCWSTR title, SHORT color = 0x0F);
		VOID Display();

		VOID ProcessEvents(EventProcessor* EP, Renderer* re);
	private:
		typedef struct _MenuBarPropreties
		{
			BYTE sizeX;
			SHORT surface;
			SHORT color;
		}MenuBarProp;
		typedef struct _MenuButtonPropreties
		{
			LPCWSTR menuTitle;
			Menu* RedirectMenuBox;
			SHORT MenuButtonColor;
		}MenuButtonProp;
		std::vector<MenuButtonProp> m_vecMenuButton;

		friend class UgrCGE;
		SHORT m_n16BorderChar;
		SHORT m_n16BorderColor = 0x0F;

		Vector2i m_vecBufferSize;
		Vector2i m_vecPosition = Vector2i(1, 1);

		CHAR_INFO* m_Buffer;
		RenderElements re;

		LPCWSTR m_Paneltitle;
		SHORT m_PanelTitleColor;

		MenuBarProp m_MenuBarProp;
	};
}