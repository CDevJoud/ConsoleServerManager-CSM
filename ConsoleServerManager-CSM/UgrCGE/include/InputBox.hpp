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
#include <Vector.hpp>
#include <Renderer.hpp>
#include <conio.h>
#include <EventProcessor.hpp>

namespace ugr
{
	class InputBox : private Renderer
	{
	public:
		~InputBox();
		VOID CreateBox(Vector2i size);
		VOID SetPosition(Vector2i pos);
		VOID Clean();
		VOID ProcessEvent(EventProcessor* EP);
		std::wstring GetStrInput() const;
		VOID ResetStrInput();
		BOOL IsFocused() const;
		BOOL Submited();
		VOID SetTitle(LPCWSTR title, SHORT col);
	private:
		VOID ProcessKeyInput();
		std::wstring m_strInput;
		VOID RenderSilent();
		VOID CleanStrFromJunk(std::wstring& str);
		friend class Panel;
		Vector2i m_size;
		Vector2i m_pos;
		Vector2i m_posRelativeToConsole;
		RenderElements re;
		BOOL m_bEnableInput = FALSE;
		BOOL m_bHasSumbited = FALSE;
		LPCWSTR m_title;
		SHORT m_n16TitleColor;
		SHORT m_n16ColorBorder = 0x08;
	};
}