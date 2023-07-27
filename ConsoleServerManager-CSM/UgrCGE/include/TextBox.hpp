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
#include <Vector.hpp>
#include <vector>
#include <string>
#include <Renderer.hpp>
#include <EventProcessor.hpp>
namespace ugr
{
	class TextBox : private Renderer
	{
	public:
		~TextBox();
		VOID Clean();
		VOID CreateBox(Vector2i size);
		VOID SetPosition(Vector2i pos);
		VOID AddLine(LPCWSTR str);
		VOID SetTextBoxColor(SHORT color);
		INT GetScrollPosition() const { return this->m_nScrollPosition; }
		VOID MoveUp() { this->m_nScrollPosition--; }
		VOID MoveDown() { this->m_nScrollPosition++; }
		INT GetLinesSize() const { return m_vecLines.size(); }
	private:
		VOID RenderSilent();		
		friend class Panel;
		Vector2i m_size;
		RenderElements re;
		Vector2i m_pos;

		std::vector<std::wstring> m_vecLines;
		int m_nVisibleHeight; // Height of the visible region
		int m_nScrollPosition = 0; // Current scroll position
		SHORT m_n16Color = 0x00;


		Vector2i m_scrollbarPosition;
		int m_nScrollBarHeight;
	};
}