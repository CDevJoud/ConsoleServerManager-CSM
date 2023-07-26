#pragma once
#include <Ugarit.hpp>
#include <RemoteControl.hpp>
#include <stack>
using namespace ugr;

class Application : private UgrCGE
{
public:
	Application();
	INT Run();
private:
	Panel MainMenu;
	std::stack<IExtreme::Application::CSM::State*> m_states;
};