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

#include <RemoteControl.hpp>

namespace IExtreme::Application::CSM
{
	RemoteControl::RemoteControl(UgrCGE* CGE) : State(CGE)
	{

	}
	VOID RemoteControl::CreateInputBoxes()
	{
		InputBox* inb0 = new InputBox;
		inb0->CreateBox(Vector2i(40, 1));
		inb0->SetPosition(Vector2i(2, 3));
		inb0->SetTitle(L"{Enter Host}", 0x8F);
		this->m_mapInputs.insert(std::pair<std::string, InputBox*>("Host", inb0));

		InputBox* inb1 = new InputBox;
		inb1->CreateBox(Vector2i(40, 1));
		inb1->SetPosition(Vector2i(2, 7));
		inb1->SetTitle(L"{Enter Port}", 0x8F);
		this->m_mapInputs.insert(std::pair<std::string, InputBox*>("Port", inb1));

		InputBox* inb2 = new InputBox;
		inb2->CreateBox(Vector2i(40, 1));
		inb2->SetPosition(Vector2i(2, 11));
		inb2->SetTitle(L"{Enter Pass}", 0x8F);
		this->m_mapInputs.insert(std::pair<std::string, InputBox*>("Pass", inb2));

	}
	BOOL RemoteControl::OnCreate()
	{
		this->CreateInputBoxes();
		this->m_Panel->CreatePanel(Vector2i(235, 73));
		this->m_Panel->SetTitle(L"RemoteControl");
		
		this->m_ConnectPanel->CreatePanel(Vector2i(45, 15));
		this->m_ConnectPanel->SetPosition(Vector2i(240 / 2 - 22, 75 / 2 - 7));
		this->m_ConnectPanel->SetTitle(L"Connect To RemoteControl", 0x0A);

		this->input.CreateBox(Vector2i(230, 1));
		this->input.SetPosition(Vector2i(1, 53));

		this->box->CreateBox(Vector2i(230, 50));
		this->box->SetPosition(Vector2i(1, 1));
		this->box->AddLine(L"Enter Host:");
		return TRUE;
	}
	BOOL RemoteControl::OnUpdate()
	{
		if (this->m_IsConnected)
		{
			if (CGE->Keyboard(VK_UP).bStrokeIsHeld && box->GetScrollPosition() > 0) this->box->MoveUp();
			if (CGE->Keyboard(VK_DOWN).bStrokeIsHeld && box->GetScrollPosition() < static_cast<int>(box->GetLinesSize()) - (50)) this->box->MoveDown();
			if (this->CGE->Keyboard(VK_PRIOR).bStrokeIsHeld && box->GetScrollPosition() > 0) for (INT i = 0; i < 10; i++) this->box->MoveUp();
			if (this->CGE->Keyboard(VK_NEXT).bStrokeIsHeld && box->GetScrollPosition() < static_cast<int>(box->GetLinesSize() - 50)) for (INT i = 0; i < 10; i++) this->box->MoveDown();
			
			input.ProcessEvent(CGE);
			if (input.Submited())
			{
				std::wstring cmd = input.GetStrInput();
				if (cmd == L"exit()")
					this->m_bQuit = TRUE;
				this->input.ResetStrInput();
			}
		}
		else
		{
			for (auto& i : this->m_mapInputs)
			{
				i.second->ProcessEvent(this->CGE);

				if (i.second->Submited())
				{
					if (i.first == "Host")
					{
						std::wstring str = i.second->GetStrInput();
						this->host = PSTR(str.c_str());
						MessageBox(NULL, str.c_str(), L"Hi", MB_OK | MB_ICONINFORMATION);
					}
					if (i.first == "Port")
					{
						std::wstring str = i.second->GetStrInput();
						this->host = PSTR(str.c_str());
					}
					if (i.first == "Pass")
					{
						std::wstring str = i.second->GetStrInput();
						this->host = PSTR(str.c_str());
					}
				}
			}
		}
		
		return TRUE;
	}
	BOOL RemoteControl::OnRender()
	{
		if (this->m_IsConnected)
		{
			this->m_Panel->ClearScreen(0x2588, 0x01);

			this->m_Panel->RenderTextBox(box);
			this->m_Panel->RenderInputBox(&input);
			this->m_Panel->Display();

			this->CGE->RenderPanel(*this->m_Panel);
		}
		else
		{
			this->m_ConnectPanel->ClearScreen(0x2588, 0x08);

			for (auto& i : this->m_mapInputs)
				this->m_ConnectPanel->RenderInputBox(i.second);

			this->m_ConnectPanel->Display();
			this->CGE->RenderPanel(*this->m_ConnectPanel);
		}

		return TRUE;
	}
	BOOL RemoteControl::Clean()
	{
		input.Clean();
		box->Clean();
		delete this->m_Panel;
		delete this->m_ConnectPanel;
		for (auto& i : this->m_mapInputs)
			i.second->Clean();
		this->m_mapInputs.clear();
		return TRUE;
	}
	
	
	///
	///
	///
	///Private Code
	///
	///
	///
	
	RemoteControl::RemoteControlPacket* RemoteControl::BuildRemoteControlPacket(INT ID, INT CMD, PSTR s1)
	{
		static RemoteControlPacket packet = { 0, 0, 0, {0x00} };

		packet.size = sizeof(INT) * 2 + strlen(s1) + 2;
		packet.ID = ID;
		packet.cmd = CMD;
		strncpy(packet.data, s1, MAX_BUFFER_DATA - 1);
		return &packet;
	}
	INT RemoteControl::SendPacket(INT s, RemoteControlPacket* packet)
	{
		INT len;
		INT total = 0;
		INT bytesLeft;
		INT ret = -1;

		bytesLeft = len = packet->size + sizeof(INT);

		while (total < len)
		{
			ret = send(s, (PSTR)packet + total, bytesLeft, 0);
			if (ret == -1) break;
			total += ret;
			bytesLeft -= ret;
		}

		return (ret == -1) ? -1 : 1;
	}
	RemoteControl::RemoteControlPacket* RemoteControl::RecievePacket(INT s)
	{
		INT pSize;
		static RemoteControlPacket packet = { 0, 0, 0, {0x00} };

		INT ret = recv(s, PSTR(&pSize), sizeof(INT), 0);

		if (ret == 0)
		{
			MessageBox(NULL, L"Connection Lost", L"Error", MB_OK | MB_ICONERROR);
			this->m_bIsConnectionAlive = FALSE;
			return NULL;
		}

		if (ret != sizeof(INT))
		{
			MessageBox(NULL, std::wstring(L"Invalid packet size" + std::to_wstring(ret)).c_str(), L"Error", MB_OK | MB_ICONERROR);
			this->m_bIsConnectionAlive = FALSE;
			return NULL;
		}

		if (pSize < 10 || pSize > 4096)
		{
			if (pSize > 4096 || pSize < 0) pSize = 4096;
			this->CleanIncoming(s, pSize);

			return NULL;
		}

		packet.size = pSize;

		INT received = 0;
		while (received < pSize)
		{
			ret = recv(s, (PSTR)&packet + sizeof(INT) + received, pSize - received, 0);
			if (ret == 0)
			{
				MessageBox(NULL, L"Connection lost", L"Error", MB_OK | MB_ICONERROR);
				this->m_bIsConnectionAlive = FALSE;
				return NULL;
			}
			received += ret;
		}
		return &packet;
	}
	INT RemoteControl::ConnectToServer(LPCSTR host, LPCSTR port)
	{
		SOCKET ss;

		struct addrinfo hint;
		struct addrinfo* serverInfo, *pServerInfo;

		ZeroMemory(&hint, sizeof(hint));
		hint.ai_family = AF_UNSPEC;
		hint.ai_socktype = SOCK_STREAM;
		hint.ai_protocol = IPPROTO_TCP;

		if (getaddrinfo(host, port, &hint, &serverInfo))
		{
			MessageBox(NULL, L"Unkown Host!", L"Error", MB_OK | MB_ICONERROR);
			this->m_bQuit = TRUE;
		}

		for (pServerInfo = serverInfo; pServerInfo != NULL; pServerInfo->ai_next)
		{
			ss = socket(pServerInfo->ai_family, pServerInfo->ai_socktype, pServerInfo->ai_protocol);

			if (ss == -1)
				continue;

			if (connect(ss, pServerInfo->ai_addr, pServerInfo->ai_addrlen))
			{
				this->ShutDownSocket(ss);
				continue;
			}
			break;
		}
		freeaddrinfo(serverInfo);
		return ss;
	}
	VOID RemoteControl::InitWindowSocket()
	{
		WSADATA ws;
		WORD version = MAKEWORD(2, 2);
		if (WSAStartup(version, &ws))
			MessageBox(NULL, L"Windowsocket Startup Failed", L"Error", MB_OK | MB_ICONERROR);
	}
	INT RemoteControl::CleanIncoming(SOCKET s, INT size)
	{
		PSTR tmp = new CHAR[size];
		INT ret = recv(s, tmp, size, 0);
		if (ret)
		{
			MessageBox(NULL, L"Connection Lost", L"Error", MB_OK | MB_ICONERROR);
			this->m_bIsConnectionAlive = FALSE;
		}
		return ret;
	}
	
	VOID RemoteControl::ShutDownSocket(SOCKET SD)
	{
		closesocket(SD);
		WSACleanup();
	}
	INT RemoteControl::RemoteControlAuthenticate(SOCKET s, PSTR pass)
	{
		INT ret;

		RemoteControlPacket* packet = this->BuildRemoteControlPacket(0x10, 3, pass);

		if (!this->SendPacket(s, packet))
			return 0;
		packet = this->RecievePacket(s);
		if (packet == NULL)
			return 0;

		return (packet->ID == -1) ? 0 : 1;
	}
}
