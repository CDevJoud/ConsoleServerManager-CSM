#pragma once
#include <Windows.h>
#include <chrono>
#include <Renderer.hpp>
#include <string>
#include <Shape.hpp>
#include <Panel.hpp>
#include <EventProcessor.hpp>
namespace ugr
{
	typedef Vector2<int> Vector2i;
	class UgrCGE : public Renderer, public EventProcessor
	{
	private:
	public:
		UgrCGE();
		FLOAT dt;
		std::string GetStrFPS() const;
		FLOAT GetFPS() const;
		VOID SetFullScreen(BOOL sw);
		
		BOOL InitConsoleWindow();
		BOOL CreateConsoleBufferWindow(Vector2i conWinSize, Vector2i fontSize = Vector2i(8, 16));
		BOOL IsInit();
		VOID Freeze(INT FreezeLevel);
		VOID RenderShape(Shape& shape);
		VOID RenderPanel(Panel& panel);
		HANDLE GetNativeHandle();
		
		VOID ProcessFPS();

		VOID Display();
	
	private:
		HANDLE m_handleConsole = NULL;

		std::chrono::system_clock::time_point tp1 = std::chrono::system_clock::now();
		std::chrono::system_clock::time_point tp2 = std::chrono::system_clock::now();
		Vector2i m_screen;
		HANDLE m_handleConsoleInput = NULL;
		SMALL_RECT m_rectConsoleWindow;
		CHAR_INFO* m_bufferScreen = NULL;
		RenderElements re = {};
	};
	
}