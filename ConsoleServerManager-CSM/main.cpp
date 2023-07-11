#include "Ugarit.hpp"
using namespace ugr;

int main()
{
	//Creating an Instance of ConsoleGraphicsEngine
	UgrCGE CGE;
	CGE.InitConsoleWindow();
	CGE.CreateConsoleBufferWindow(Vector2i(240, 64));
	
	Shape shape;

	//If the Instance Init successfully the application loop will start
	while (CGE.IsInit())
	{
		CGE.ClearScreen();

		//Hello World Triangle

		CGE.Display();
	}
	return 0;
}