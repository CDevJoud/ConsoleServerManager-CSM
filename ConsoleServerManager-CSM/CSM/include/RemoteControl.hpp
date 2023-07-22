#pragma once
#include <State.hpp>

using namespace ugr;
namespace IExtreme::Application::CSM
{
	class RemoteControl : public State
	{
	public:
		RemoteControl(UgrCGE* CGE);

		BOOL OnCreate();
		BOOL OnUpdate();
		BOOL OnRender();
		BOOL Clean();
	private:
		TextBox box;
		Panel* m_Panel = new Panel;
	};
}