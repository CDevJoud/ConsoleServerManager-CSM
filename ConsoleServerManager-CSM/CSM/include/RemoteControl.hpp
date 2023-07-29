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
#define MAX_BUFFER_DATA 4096
#define WIN32_LEAN_AND_MEAN
#include <ws2tcpip.h>
#include <winsock2.h>
#include <State.hpp>
#include <map>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

using namespace ugr;
namespace IExtreme::Application::CSM
{
	class RemoteControl : public State
	{
	public:
		RemoteControl(UgrCGE* CGE);

		//Overided Virtual Functions
	public:
		BOOL OnCreate();
		BOOL OnUpdate();
		BOOL OnRender();
		BOOL Clean();
	private:

		struct RemoteControlPacket
		{
			INT size;
			INT ID;
			INT cmd;
			CHAR data[MAX_BUFFER_DATA];
		};

		RemoteControlPacket* BuildRemoteControlPacket(INT ID, INT CMD, PSTR s1);

		INT SendPacket(INT s, RemoteControlPacket* packet);
		RemoteControlPacket* RecievePacket(INT s);
		INT ConnectToServer(LPCSTR host, LPCSTR port);
		VOID InitWindowSocket();
		VOID ShutDownSocket(SOCKET SD);
		INT RemoteControlAuthenticate(SOCKET sock, PSTR pass);
		INT CleanIncoming(SOCKET s, INT size);

		VOID PrintPacket(RemoteControlPacket* packet);
		INT TerminalMode(SOCKET s);
		INT RemoteControlCommand(SOCKET s, PSTR command);
		INT m_nRemoteSocket;
		BOOL RawOutput = TRUE;

	private:
		VOID CreateInputBoxes();
		VOID CreateButtons();
	private:
		TextBox* box = new TextBox;
		InputBox input;
		Panel* m_Panel = new Panel;
		
		Panel* m_ConnectPanel = new Panel;
		std::map<std::string, InputBox*> m_mapInputs;
		std::map<std::string, Button*> m_mapBtn;

		BOOL m_bFullScreen = TRUE;
		std::string host, pass, port;
		BOOL m_IsConnected = FALSE;

		BOOL m_bIsConnectionAlive = FALSE;

		FLOAT m_nRadius;
	};
}