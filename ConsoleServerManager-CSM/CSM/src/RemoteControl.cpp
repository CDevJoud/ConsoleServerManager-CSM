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

		this->box.CreateBox(Vector2i(30, 40));
		this->box.SetPosition(Vector2i(1, 1));
		for (int i = 0; i < 1000; i++)
			this->box.AddLine(std::wstring(L"Lines" + std::to_wstring(i)).c_str());
		return TRUE;
	}
	BOOL RemoteControl::OnUpdate()
	{
		if (this->CGE->Keyboard(VK_ESCAPE).bStrokeReleased) this->m_bQuit = TRUE;
		if (CGE->Keyboard(VK_UP).bStrokeIsHeld && box.GetScrollPosition() > 0) this->box.MoveUp();
		if (CGE->Keyboard(VK_DOWN).bStrokeIsHeld && box.GetScrollPosition() < static_cast<int>(box.GetLinesSize()) - 40 + 1) this->box.MoveDown();
		return TRUE;
	}
	BOOL RemoteControl::OnRender()
	{
		this->m_Panel->ClearScreen();

		this->m_Panel->RenderTextBox(&box);

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
