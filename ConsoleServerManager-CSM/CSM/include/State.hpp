#pragma once
#include <Ugarit.hpp>
using namespace ugr;
namespace IExtreme::Application::CSM
{
	class State
	{
	public:
		State(ugr::UgrCGE* CGE);

		virtual BOOL OnCreate() = 0;
		virtual BOOL OnUpdate() = 0;
	protected:
		ugr::UgrCGE* CGE = NULL;
	};
}