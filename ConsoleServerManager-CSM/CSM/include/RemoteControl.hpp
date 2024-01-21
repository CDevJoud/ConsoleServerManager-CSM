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
#include <ws2tcpip.h>
#include <winsock2.h>
#include <State.hpp>
#include <string>
#include <map>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

namespace IExtreme::Application::CSM
{
	
	class RemoteControl : public State
	{
	public:
		RemoteControl(ugr::ConsoleWindow* CGE);

		//Overided Virtual Functions
	public:
		int OnCreate();
		int OnUpdate();
		int OnRender();
		int Clean();
	private:

		struct RemoteControlPacket
		{
			int size;
			int ID;
			int cmd;
			ugr::CHAR data[MAX_BUFFER_DATA];
		};

		RemoteControlPacket* BuildRemoteControlPacket(INT ID, INT CMD, PSTR s1);

		ugr::INT SendPacket(ugr::INT s, RemoteControlPacket* packet);
		RemoteControlPacket* RecievePacket(INT s);
		int ConnectToServer(ugr::LPCSTR host, ugr::LPCSTR port);
		VOID InitWindowSocket();
		VOID ShutDownSocket(SOCKET SD);
		int RemoteControlAuthenticate(SOCKET sock, PSTR pass);
		int CleanIncoming(SOCKET s, INT size);

		VOID PrintPacket(RemoteControlPacket* packet);
		int TerminalMode(SOCKET s);
		int RemoteControlCommand(SOCKET s, PSTR command);
		int m_nRemoteSocket;
		ugr::BOOL RawOutput = TRUE;

	private:
		VOID CreateInputBoxes();
		VOID CreateButtons();
	private:
		ugr::TextBox* box = new ugr::TextBox;
		ugr::InputBox input;
		ugr::Panel* m_Panel = new ugr::Panel;
		
		ugr::Panel* m_ConnectPanel = new ugr::Panel;
		std::map<std::string, ugr::InputBox*> m_mapInputs;
		std::map<std::string, ugr::Button*> m_mapBtn;

		ugr::BOOL m_bFullScreen = TRUE;
		std::string host, pass, port;
		ugr::BOOL m_IsConnected = FALSE;

		ugr::BOOL m_bIsConnectionAlive = FALSE;

		FLOAT m_nRadius;
	};
}