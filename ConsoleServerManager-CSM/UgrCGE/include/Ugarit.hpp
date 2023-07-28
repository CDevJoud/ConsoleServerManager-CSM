// O------------------------------------LICENSE--------------------------------------O
// |  MIT License																	 |
// |  																				 |
// |  Copyright(c) 2023 Joud Kandeel												 |
// |  																				 |
// |  Permission is hereby granted, free of charge, to any person obtaining a copy	 |
// |  of this software and associated documentation files(the "Software"), to deal	 |
// |  in the Software without restriction, including without limitation the rights	 |
// |  to use, copy, modify, merge, publish, distribute, sublicense, and /or sell	 |
// |  copies of the Software, and to permit persons to whom the Software is			 |
// |  furnished to do so, subject to the following conditions :						 |
// |  																				 |
// |  The above copyright noticeand this permission notice shall be included in all	 |
// |  copies or substantial portions of the Software.								 |
// |  																				 |
// |  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 |
// |  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,		 |
// |  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE	 |
// |  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER		 |
// |  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	 |
// |  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	 |
// |  SOFTWARE.																		 |
// O---------------------------------------------------------------------------------O

#pragma once
#include <ws2tcpip.h>
#include <winsock2.h>
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
		
		VOID ShutDownCGE();
	private:
		VOID SetUpFrame(Vector2i pos, Vector2i size, SHORT color);
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