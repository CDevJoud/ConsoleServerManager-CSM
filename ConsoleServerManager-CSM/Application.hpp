#pragma once
#include <Ugarit.hpp>
using namespace ugr;

class Application : private UgrCGE
{
public:
	INT Run();
private:
	Panel MainMenu;
};