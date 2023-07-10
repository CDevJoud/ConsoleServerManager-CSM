#include "Ugarit.hpp"
using namespace ugr;

int main()
{
	//Creating an Instance of ConsoleGraphicsEngine
	UgrCGE CGE;
	CGE.InitConsoleWindow();
	CGE.CreateConsoleBufferWindow(Vector2i(240, 64));


	//If the Instance Init successfully the application loop will start
	while (CGE.IsInit())
	{
		CGE.ClearScreen();

		//Hello World Triangle
		CGE.RasterizeTriangle(Vector2i(120, 0), Vector2i(0, 63), Vector2i(240, 63), 0x2591, 0x0F);

		CGE.Display();
	}
	return 0;
}