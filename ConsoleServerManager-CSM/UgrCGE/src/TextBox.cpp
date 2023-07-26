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

#include <TextBox.hpp>

namespace ugr
{
	TextBox::~TextBox()
	{
		this->m_vecLines.clear();
		this->m_vecLines.shrink_to_fit();
	}
	VOID TextBox::Clean()
	{
		this->m_vecLines.clear();
		this->m_vecLines.shrink_to_fit();
	}
	VOID TextBox::CreateBox(Vector2i size)
	{
		this->m_size = size;
		this->m_scrollbarPosition.x = size.x;
		this->m_scrollbarPosition.y = 1;
		this->m_nScrollBarHeight = size.y - 2;
		this->m_nVisibleHeight = size.y;
		this->re.buffer = new CHAR_INFO[this->m_size.x * this->m_size.y]{};
		this->re.screen = size;
		this->InitRenderer(re);
	}
	VOID TextBox::SetPosition(Vector2i pos)
	{
		this->m_pos = pos;
	}
	VOID TextBox::AddLine(LPCSTR str)
	{
		this->m_vecLines.push_back(str);
	}
	VOID TextBox::SetTextBoxColor(SHORT color)
	{
		this->m_n16Color = color;
	}
	VOID TextBox::RenderSilent()
	{
		this->ClearScreen();
		// Draw the visible lines
		for (int y = 0; y < this->m_nVisibleHeight; y++)
		{
			int lineIndex = y + this->m_nScrollPosition;
			if (lineIndex >= 0 && lineIndex < static_cast<int>(this->m_vecLines.size()))
			{
				this->RenderText(Vector2i(0, y), this->m_vecLines[lineIndex].c_str());
			}
		}
	}
}