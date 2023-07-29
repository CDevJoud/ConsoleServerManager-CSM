// O------------------------------------LICENSE--------------------------------------O
// |  MIT License																	 |
// |  																				 |
// |  Copyright(c) 2023 Joud Kandeel												 |
// |  																				 |
// |  Permission is hereby granted, free of charge, to any person obtaining a copy	 |
// |  of this software and associated documentation files(the "Software"), to deal	 |
// |  in the Software without restriction, including without limitation the rights	 |
// |  to use, copy, modify, merge, publish, distribute, sublicense, and /or sell	 |
// |  copies of the Software, and to permit persons to whom the Software is			 |
// |  furnished to do so, subject to the following conditions :						 |
// |  																				 |
// |  The above copyright noticeand this permission notice shall be included in all	 |
// |  copies or substantial portions of the Software.								 |
// |  																				 |
// |  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 |
// |  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,		 |
// |  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE	 |
// |  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER		 |
// |  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	 |
// |  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	 |
// |  SOFTWARE.																		 |
// O---------------------------------------------------------------------------------O

#pragma once
#include <Windows.h>
#include <Renderer.hpp>
#include <Menu.hpp>
#include <unordered_map>
#include <EventProcessor.hpp>
#include <string>
#include <TextBox.hpp>
#include <InputBox.hpp>
#include <Button.hpp>
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

		VOID RenderTextBox(TextBox* box);
		VOID RenderInputBox(InputBox* box);
		VOID RenderButton(Button* btn);

		VOID SetTitle(LPCWSTR title, SHORT color = 0x0F);
		VOID Display();

		VOID ProcessEvents(EventProcessor* EP);
	private:
		VOID SetUpFrame(Vector2i pos, Vector2i size, SHORT color = 0x0F);
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