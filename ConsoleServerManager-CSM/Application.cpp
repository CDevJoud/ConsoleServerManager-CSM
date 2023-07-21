#include "Application.hpp"

INT Application::Run()
{
	this->InitConsoleWindow();
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

		SetConsoleTitle(std::to_wstring(this->GetFPS()).c_str());

		this->RenderPanel(this->MainMenu);
		this->SetPixel(this->GetMousePos());
		this->Display();
	}
	return EXIT_SUCCESS;
}