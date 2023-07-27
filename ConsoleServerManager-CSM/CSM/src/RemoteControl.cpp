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

#include <RemoteControl.hpp>
namespace IExtreme::Application::CSM
{
	RemoteControl::RemoteControl(UgrCGE* CGE) : State(CGE)
	{

	}
	BOOL RemoteControl::OnCreate()
	{
		this->m_Panel->CreatePanel(Vector2i(235, 73));
		this->m_Panel->SetTitle(L"RemoteControl");

		this->input.CreateBox(Vector2i(230, 1));
		this->input.SetPosition(Vector2i(1, 53));

		this->box->CreateBox(Vector2i(230, 50));
		this->box->SetPosition(Vector2i(1, 1));
		/*for (int i = 0; i < 1'0000; i++)
			this->box->AddLine(std::wstring(L"Lines " + std::to_wstring(i)).c_str());*/
		return TRUE;
	}
	BOOL RemoteControl::OnUpdate()
	{
		if (CGE->Keyboard(VK_UP).bStrokeIsHeld && box->GetScrollPosition() > 0) this->box->MoveUp();
		if (CGE->Keyboard(VK_DOWN).bStrokeIsHeld && box->GetScrollPosition() < static_cast<int>(box->GetLinesSize()) - (50)) this->box->MoveDown();
		if (this->CGE->Keyboard(VK_PRIOR).bStrokeIsHeld && box->GetScrollPosition() > 0) for (INT i = 0; i < 10; i++) this->box->MoveUp();
		if (this->CGE->Keyboard(VK_NEXT).bStrokeIsHeld && box->GetScrollPosition() < static_cast<int>(box->GetLinesSize() - 50)) for (INT i = 0; i < 10; i++) this->box->MoveDown();
		
		input.ProcessEvent(CGE);
		if (input.Submited())
		{
			std::wstring cmd = input.GetStrInput();
			if (cmd == L"exit()")
				this->m_bQuit = TRUE;
			if (cmd == L"echo")
				for (int i = 0; i < 1'000; i++)
					this->box->AddLine(std::wstring(L"Lines " + std::to_wstring(i)).c_str());

			this->box->AddLine(input.GetStrInput().c_str());
			if (cmd == L"cls")
				this->box->ResetTextBox();
			if (cmd == L"std::cout << \"Hello World\" << std::endl;")
				this->box->AddLine(L"Hello World");
			this->input.ResetStrInput();
		}
		return TRUE;
	}
	BOOL RemoteControl::OnRender()
	{
		this->m_Panel->ClearScreen(0x2588, 0x01);

		this->m_Panel->RenderTextBox(box);
		this->m_Panel->RenderInputBox(&input);
		this->m_Panel->Display();

		this->CGE->RenderPanel(*this->m_Panel);
		return TRUE;
	}
	BOOL RemoteControl::Clean()
	{
		input.Clean();
		box->Clean();
		delete this->m_Panel;
		return TRUE;
	}
}
