#include "Application.hpp"


//this is a test for reading from the log
//VOID Application::Run()
//{
//	this->InitConsoleWindow();
//	this->CreateConsoleBufferWindow(Vector2i(240, 105), Vector2i(8, 10));
//
//	Panel panel;
//	panel.CreatePanel(Vector2i(126, 100));
//	panel.SetPosition(Vector2i(1, 1));
//	panel.RenderLine(Vector2i(0, 0), Vector2i(126, 0), 0x2588, 0xF8);
//	panel.AddMenuToBar(L"File", Vector2i(2, 0), 0x8F);
//	panel.RenderCircle(Vector2i(110 + 10, 32), 20);
//
//    STARTUPINFO si = {sizeof(STARTUPINFO)};
//    PROCESS_INFORMATION pi;
//    /*if (!CreateProcess(L"C:/SFML-2.5.1/start.bat", nullptr, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi))
//        exit(10);*/
//    // Path to the log file directory
//    const wchar_t* logDirectory = L"Logs";
//    const wchar_t* logFileName = L"latest.log";
//    // Keep track of the file size
//    DWORD fileSize = 0;
//    std::vector<std::string> dataLines;
//    int begining = 0;
//	while (this->IsInit())
//	{
//        // Find the latest log file in the directory
//        WIN32_FIND_DATA findData;
//        HANDLE hFind = FindFirstFileW((std::wstring(logDirectory) + L"\\" + logFileName).c_str(), &findData);
//        if (hFind != INVALID_HANDLE_VALUE) {
//            // Open the log file
//            HANDLE hFile = CreateFileW((std::wstring(logDirectory) + L"\\" + findData.cFileName).c_str(),
//                GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
//            if (hFile != INVALID_HANDLE_VALUE) {
//                // Move the file pointer to the end
//                SetFilePointer(hFile, fileSize, nullptr, FILE_BEGIN);
//
//                // Read and process the new log lines
//                char buffer[4096]; ZeroMemory(buffer, 4096);
//                DWORD bytesRead;
//                while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0) {
//                    fileSize += bytesRead;
//                    /*
//                    for (int i = 0; i < bytesRead; i++)
//                        data[i + fileSize] = buffer[i];*/
//                    std::string line(buffer, bytesRead);
//                    std::string buff;
//                    for (int i = 0; i < line.size(); i++)
//                    {
//                        if (line[i] != 0x0A)
//                        {
//                            buff.push_back(line[i]);
//                        }
//                        else
//                        {
//                            dataLines.push_back(buff);
//                            buff = "";
//                        }
//                    }
//                }
//
//                // Close the log file
//                CloseHandle(hFile);
//            }
//            else {
//                std::cerr << "Failed to open the log file." << std::endl;
//                exit(1);
//            }
//
//            // Close the find handle
//            FindClose(hFind);
//        }
//        else {
//            std::cerr << "Failed to find the log file." << std::endl;
//            exit(1);
//        }
//
//        panel.ClearScreen();
//		this->ClearScreen();
//        this->RenderCircle(Vector2i(111 + 10, 33), 20, 0x2588, 0x01);
//        int Line = 1;
//        
//        /*for (int i = 0; i < data.size(); i++)
//        {
//            if (data[i] == 0x0A)
//            {
//                panel.RenderText(Vector2i(0, Line), buf.c_str());
//                buf = "";
//                Line++;
//            }
//            else
//                buf += data[i];
//        }*/
//        
//        /*for (auto& i : dataLines)
//        {
//            
//            panel.RenderText(Vector2i(0, Line), i.c_str());
//            Line++;
//        }*/
//        panel.RenderLine(Vector2i(0, 0), Vector2i(126, 0), 0x2588, 0xF8);
//        panel.AddMenuToBar(L"Server Log", Vector2i(2, 0), 0x8F);
//        panel.RenderCircle(Vector2i(110 + 10, 32), 20);
//        for (int i = begining; i < dataLines.size(); i++)
//        {
//            this->RenderText(Vector2i(0, Line), dataLines[i].c_str());
//            Line++;
//        }
//        if(_kbhit())
//        switch (_getch())
//        {
//        default:
//            break;
//        case 'w':
//            begining--;
//            break;
//
//        case 's':
//            begining++;
//            break;
//        }
//        //data.clear();
//		//this->Render(panel);
//        this->Display();
//	}
//}

VOID Application::Run()
{
	this->InitConsoleWindow();
	this->CreateConsoleBufferWindow(Vector2i(64, 64), Vector2i(16, 16));
	std::vector<std::string> file;
	for (int i = 0; i < 256; i++)
		file.push_back("this is a value" + std::to_string(i));
	int lineBegin = 0;
	Panel start;
	start.CreatePanel(Vector2i(32, 32));
	Vector2i startpos(31, 31);
	start.SetPosition(startpos);

	while (this->IsInit())
	{
		this->ClearScreen();
		start.ClearScreen();
		start.RenderLine(Vector2i(0, 0), Vector2i(240, 0), 0x2588, 0x08);
		start.RenderText(Vector2i(2, 0), "File", 0x8F);
		int line = 1;
		for (int i = lineBegin; i < file.size(); i++)
		{
			start.RenderText(Vector2i(0, line), file[i].c_str());
			line++;
		}
		if (_kbhit())
		{
			switch (_getch())
			{
			default:
				break;
			case'w':
				lineBegin--;
				break;

			case 's':
				lineBegin++;
				break;

			case 'i':
				startpos.y--;
				break;

			case 'k':
				startpos.y++;
				break;

			case 'l':
				startpos.x++;
				break;

			case 'j':
				startpos.x--;
				break;
			}
			start.SetPosition(startpos);
			if (lineBegin <= 0)
				lineBegin = 0;
		}
		this->Render(start);
		this->Display();
	}
}