#include "Application.hpp"

VOID Application::Run()
{
	this->InitConsoleWindow();
	this->CreateConsoleBufferWindow(Vector2i(240, 64));
	
	while (this->IsInit())
	{
		this->ClearScreen();

		this->Display();
	}
}