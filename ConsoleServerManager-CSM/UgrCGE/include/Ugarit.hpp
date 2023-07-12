#pragma once
#include <Windows.h>
#include "Renderer.hpp"
#include "Shape.hpp"
#include "Panel.hpp"
namespace ugr
{
	typedef Vector2<int> Vector2i;
	class UgrCGE : public Renderer
	{
	public:
		UgrCGE();
		BOOL InitConsoleWindow();
		BOOL CreateConsoleBufferWindow(Vector2i conWinSize, Vector2i fontSize = Vector2i(8, 16));
		BOOL IsInit();
		VOID Freeze(INT FreezeLevel);
		VOID Render(Shape& shape);
		VOID Render(Panel& panel);
		HANDLE m_handleConsole;
		VOID Display();
	private:
		Vector2i m_screen;
		
		HANDLE m_handleConsoleInput;
		SMALL_RECT m_rectConsoleWindow;
		CHAR_INFO* m_bufferScreen;
		RenderElements re = {};
	};
	
}