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

#include "Application.hpp"

Application::Application()
{
	this->InitConsoleWindow();
	this->CreateConsoleBufferWindow(Vector2i(240, 75), Vector2i(8, 14));
	this->m_states.push(new IExtreme::Application::CSM::RemoteControl(this));
	this->m_states.top()->OnCreate();
}

INT Application::Run()
{
	/*this->InitConsoleWindow();
	this->CreateConsoleBufferWindow(Vector2i(240, 75), Vector2i(8, 14));
	Menu* m = new Menu;
	Menu* m1 = new Menu;
	m->CreateMenu(Vector2i(10, 20));
	m->AddElements(L"Test");
	m->AddElements(L"LOL");

	m1->CreateMenu(Vector2i(200, 60));
	m1->AddElements(L"Test");
	m1->AddElements(L"LOL");

	for (int i = 0; i < 60; i++)
		m1->AddElements(L"LOL");
	bool full = false;

	MainMenu.CreatePanel(Vector2i(235, 73));
	MainMenu.SetTitle(L"--{MainMenu}--", 0x0A);
	MainMenu.CreateMenuBar(234, 0x2588, 0x08);
	MainMenu.AddMenu(L"File", m, 0x8F);
	MainMenu.AddMenu(L"LOL", m1, 0x8F);
	

	while (this->IsInit())
	{
		this->ProcessEvents();
		this->ProcessFPS();

		if (this->Keyboard(VK_ESCAPE).bStrokePressed)
			break;

		if (this->Keyboard(L'J').bStrokePressed)
		{
			this->SetFullScreen(full);
			full = !full;
		}

		this->MainMenu.ClearScreen(0x2588, 0x01);
		this->MainMenu.ProcessEvents(this);
		this->MainMenu.Display();


		this->RenderPanel(this->MainMenu);
		this->SetPixel(this->GetMousePos());
		this->Display();
	}*/

	while (this->IsInit() && !this->m_states.top()->ToQuit())
	{
		this->ProcessEvents();
		this->ProcessFPS();
		if (!this->m_states.empty())
			this->m_states.top()->OnUpdate();

		SetConsoleTitle(std::to_wstring(this->GetFPS()).c_str());

		this->ClearScreen();
		if (!this->m_states.empty())
			this->m_states.top()->OnRender();
		this->Display();
	}
	this->m_states.top()->Clean();
	delete this->m_states.top();
	this->m_states.pop();
	return EXIT_SUCCESS;
}