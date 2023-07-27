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

#include "InputBox.hpp"
#include <string>
namespace ugr
{
	InputBox::~InputBox()
	{
		delete re.buffer;
	}
	VOID InputBox::CreateBox(Vector2i size)
	{
		this->m_size = size;
		this->re.screen = size;
		this->re.buffer = new CHAR_INFO[this->m_size.x * this->m_size.y]{};
		this->InitRenderer(re);
	}
	VOID InputBox::SetPosition(Vector2i pos)
	{
		this->m_pos = pos;
	}
	VOID InputBox::Clean()
	{
		delete re.buffer;
	}
	VOID InputBox::ProcessEvent(EventProcessor* EP)
	{
		auto mousePos = EP->GetMousePos();
		INT y1 = mousePos.y - 1;
		INT y2 = m_pos.y;
		if (mousePos.x >= this->m_pos.x && mousePos.x <= this->m_pos.x + this->m_size.x && y1 == y2)
		{
			if (EP->Mouse(EventProcessor::MouseType::Left).bStrokePressed)
			{
				this->m_bEnableInput = TRUE;
				this->m_n16ColorBorder = 0x0F;
				return;
			}
		}
		if (this->m_bEnableInput)
			this->ProcessKeyInput(EP);
		else
			this->m_bHasSumbited = FALSE;
	}
	std::wstring InputBox::GetStrInput() const
	{
		return this->m_strInput;
	}
	VOID InputBox::ResetStrInput()
	{
		this->m_strInput = L"";
	}
	BOOL InputBox::IsFocused() const
	{
		return this->m_bEnableInput;
	}
	BOOL InputBox::Submited()
	{
		return m_bHasSumbited;
	}
	VOID InputBox::ProcessKeyInput(EventProcessor* e)
	{
		SHORT c = e->GetKeyBoardPressed();
		if (c == 127 && !this->m_strInput.empty())
		{
			this->m_strInput.pop_back();
			this->m_strInput.shrink_to_fit();
		}
		if (c != NULL)
			this->m_strInput.push_back(c);
		if (c == 27)
		{
			this->m_bEnableInput = FALSE;
			this->m_n16ColorBorder = 0x08;
		}

		if (c == 13)
			this->m_bHasSumbited = TRUE;
		else
			this->m_bHasSumbited = FALSE;
		this->CleanStrFromJunk(this->m_strInput);
	}
	VOID InputBox::RenderSilent()
	{
		this->ClearScreen();
		this->RenderText(Vector2i(0, 0), this->m_strInput.c_str());
	}
	VOID InputBox::CleanStrFromJunk(std::wstring& str)
	{
		std::wstring tmp;
		for (auto& i : str)
			if (i != 127 && i != 1 && i != 13 && i != 27)
				tmp.push_back(i);
		str = tmp;
	}
}