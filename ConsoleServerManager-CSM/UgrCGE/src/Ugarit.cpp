#include "Ugarit.hpp"
namespace ugr
{
    UgrCGE::UgrCGE()
    {
        
    }
    BOOL UgrCGE::IsInit()
    {
        return (m_handleConsole) ? TRUE : FALSE;
    }
    void UgrCGE::Freeze(INT fl)
    {
        switch (fl)
        {
        default:
            break;
        case 0:
            system("Pause>nul");
            break;
        case 1:
            while (1);
            break;
        }
    }
    void UgrCGE::RenderShape(Shape& shape)
    {
        if (shape.defShape == "Rect")
        {
            Vector2i p[4];
            p[0] = Vector2i(0, 0);
            p[1].x = shape.size.x;
            p[2] = shape.size;
            p[3].y = shape.size.y;
            this->RenderQuad(p[0] + shape.pos, p[1] + shape.pos, p[2] + shape.pos, p[3] + shape.pos, shape.surface, shape.color);
        }
        if (shape.defShape == "FillRect")
        {
            this->RasterizeQuad(shape.size, shape.pos, shape.surface, shape.color);
        }
    }
    BOOL UgrCGE::InitConsoleWindow()
    {
        this->m_handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        this->m_handleConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
        return TRUE;
    }
    BOOL UgrCGE::CreateConsoleBufferWindow(Vector2i CWS, Vector2i fontSize)
    {
        if (m_handleConsole == INVALID_HANDLE_VALUE)
            MessageBox(NULL, L"Bad Handle", L"Error", MB_ICONERROR | MB_OK);

        this->m_screen = CWS;

        this->m_rectConsoleWindow = { 0, 0, 1, 1 };
        SetConsoleWindowInfo(this->m_handleConsole, TRUE, &this->m_rectConsoleWindow);

        if (!SetConsoleScreenBufferSize(this->m_handleConsole, { SHORT(this->m_screen.x), SHORT(this->m_screen.y) }))
            MessageBox(NULL, L"Couldn't set the console screen buffer size!", L"Error", MB_ICONERROR | MB_OK);
        
        SetConsoleActiveScreenBuffer(this->m_handleConsole);

        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = NULL;
        cfi.dwFontSize.X = fontSize.x;
        cfi.dwFontSize.Y = fontSize.y;
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;

        wcscpy_s(cfi.FaceName, L"Consolas");
        SetCurrentConsoleFontEx(this->m_handleConsole, FALSE, &cfi);

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(this->m_handleConsole, &csbi);
        if (this->m_screen.x > csbi.dwMaximumWindowSize.X)
        {
            MessageBox(NULL, L"Screen Width / Font Width To Large", L"Error", MB_OK | MB_ICONERROR);
        }
        if (this->m_screen.y > csbi.dwMaximumWindowSize.Y)
        {
            MessageBox(NULL, L"Screen Height / Font Height To Large", L"Error", MB_OK | MB_ICONERROR);
        }

        this->m_rectConsoleWindow.Left = 0;
        this->m_rectConsoleWindow.Top = 0;
        this->m_rectConsoleWindow.Right = this->m_screen.x - 1;
        this->m_rectConsoleWindow.Bottom = this->m_screen.y - 1;

        SetConsoleWindowInfo(this->m_handleConsole, TRUE, &this->m_rectConsoleWindow);

        SetConsoleMode(this->m_handleConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

        this->m_bufferScreen = new CHAR_INFO[this->m_screen.x * this->m_screen.y];
        ZeroMemory(this->m_bufferScreen, sizeof(CHAR_INFO) * this->m_screen.x * this->m_screen.y);

        re.buffer = this->m_bufferScreen;
        re.hConsole = this->m_handleConsole;
        re.rectWin = this->m_rectConsoleWindow;
        re.screen = this->m_screen;
        this->InitRenderer(re);
        return 0;
    }
}