#include "State.hpp"

namespace IExtreme::Application::CSM
{
	State::State(ugr::UgrCGE* CGE) : CGE(CGE)
	{
	}
	BOOL State::ToQuit() const
	{
		return this->m_bQuit;
	}
}
