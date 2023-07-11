#include "Application.hpp"

VOID Application::Run()
{
	this->InitConsoleWindow();
	this->CreateConsoleBufferWindow(Vector2i(240, 64));
	Panel panel;
	panel.CreatePanel(Vector2i(100, 32));
	panel.SetPosition(Vector2i(240 / 2 - 50, 64 / 2 - 16));
	while (this->IsInit())
	{
		this->ClearScreen(0x2588, 0x0B);

		this->Render(panel);
		
		this->Display();
	}
}