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
		return TRUE;
	}
	BOOL RemoteControl::OnUpdate()
	{
		if (this->CGE->Keyboard(VK_ESCAPE).bStrokeReleased) this->m_bQuit = TRUE;

		return TRUE;
	}
	BOOL RemoteControl::OnRender()
	{

		this->m_Panel->ClearScreen();

		this->m_Panel->RenderText(Vector2i(235 / 2 - strlen("Hello World") / 2, 73 / 2), L"Hello World");

		this->m_Panel->Display();

		this->CGE->RenderPanel(*this->m_Panel);
		return TRUE;
	}
	BOOL RemoteControl::Clean()
	{
		delete this->m_Panel;
		return TRUE;
	}
}
