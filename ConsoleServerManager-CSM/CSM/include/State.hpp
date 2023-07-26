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
		virtual BOOL OnRender() = 0;
		virtual BOOL Clean() = 0;

		BOOL ToQuit() const;
	protected:
		BOOL m_bQuit = FALSE;
		ugr::UgrCGE* CGE = NULL;
	};
}