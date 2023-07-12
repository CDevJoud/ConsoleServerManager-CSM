#include "Application.hpp"

int main()
{
	Application app;
	app.Run();
}

#include <iostream>
#include <windows.h>

int Mmain() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Start the Minecraft server process
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    
    if (CreateProcess(L"C:/SFML-2.5.1/start.bat", nullptr, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        // Read and print the console output
        char buffer[4096];
        ZeroMemory(buffer, 4096);
        DWORD bytesRead;
        while (ReadFile(pi.hProcess, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0) {
            WriteConsole(hConsole, buffer, bytesRead, nullptr, nullptr);
        }

        // Close process handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        std::cerr << "Failed to start the Minecraft server process. " << GetLastError() << std::endl;
        char buffer[4096];
        DWORD bytesRead;
        ReadFile(pi.hProcess, buffer, sizeof(buffer), &bytesRead, nullptr);
        WriteConsole(hConsole, buffer, bytesRead, nullptr, nullptr);
        return 1;
    }
    while (1);

    return 0;
}

//#include <iostream>
//#include <windows.h>
//
//int main() {
//    // Path to the log file directory
//    const wchar_t* logDirectory = L"Logs";
//    const wchar_t* logFileName = L"latest.log";
//
//    // Keep track of the file size
//    DWORD fileSize = 0;
//
//    while (true) {
//        // Find the latest log file in the directory
//        WIN32_FIND_DATA findData;
//        HANDLE hFind = FindFirstFile((std::wstring(logDirectory) + L"\\" + logFileName).c_str(), &findData);
//        if (hFind != INVALID_HANDLE_VALUE) {
//            // Open the log file
//            HANDLE hFile = CreateFile((std::wstring(logDirectory) + L"\\" + findData.cFileName).c_str(),
//                GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
//            if (hFile != INVALID_HANDLE_VALUE) {
//                // Move the file pointer to the end
//                SetFilePointer(hFile, fileSize, nullptr, FILE_BEGIN);
//
//                // Read and process the new log lines
//                char buffer[4096];
//                DWORD bytesRead;
//                while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0) {
//                    std::cout.write(buffer, bytesRead);
//                    fileSize += bytesRead;
//                }
//
//                // Close the log file
//                CloseHandle(hFile);
//            }
//            else {
//                std::cerr << "Failed to open the log file." << std::endl;
//                return 1;
//            }
//
//            // Close the find handle
//            FindClose(hFind);
//        }
//        else {
//            std::cerr << "Failed to find the log file." << std::endl;
//            return 1;
//        }
//
//        // Delay before the next iteration (e.g., 1 second)
//        Sleep(0);
//    }
//
//    return 0;
//}
//
