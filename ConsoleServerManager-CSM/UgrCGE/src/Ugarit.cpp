#include "Ugarit.hpp"
namespace ugr
{
    UgrCGE::UgrCGE()
    {
        
    }
    BOOL UgrCGE::IsInit()
    {
        return (m_handleConsole == INVALID_HANDLE_VALUE) ? FALSE : TRUE;
    }
    VOID UgrCGE::Freeze(INT fl)
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
    VOID UgrCGE::Render(Shape& shape)
    {
        //Check RenderShape Type to Render
        if (shape.GetShapeType() == "Shape.Rect.Line")
        {
            Vector2i p[4];
            p[0] = Vector2i(0, 0);
            p[1].x = shape.GetSize().x;
            p[2] = shape.GetSize();
            p[3].y = shape.GetSize().y;
            auto pos = shape.GetPosition();
            this->RenderQuad(p[0] + pos, p[1] + pos, p[2] + pos, p[3] + pos, shape.GetChar(), shape.GetColor());
        }
        if (shape.GetShapeType() == "Shape.Rect.Fill")
        {
            this->RasterizeQuad(shape.GetSize(), shape.GetPosition(), shape.GetChar(), shape.GetColor());
        }
        if (shape.GetShapeType() == "Shape.Triangle.Line")
        {
            auto& p = shape.GetVertexArray();
            auto pos = shape.GetPosition();
            this->RenderTriangle(p[2] + pos, p[1] + pos, p[0] + pos, shape.GetChar(), shape.GetColor());
        }
        if (shape.GetShapeType() == "Shape.Triangle.Fill")
        {
            auto& p = shape.GetVertexArray();
            auto pos = shape.GetPosition();
            this->RasterizeTriangle(p[0] + pos, p[1] + pos, p[2] + pos, shape.GetChar(), shape.GetColor());
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
        //Check if handleConsole is init
        if (!this->IsInit())
            MessageBox(NULL, L"Bad Handle", L"Error", MB_ICONERROR | MB_OK);
        
        //Set screen size relative to the given parameter
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

        //Init RenderElements and Renderer
        re.buffer = this->m_bufferScreen;
        re.hConsole = this->m_handleConsole;
        re.rectWin = this->m_rectConsoleWindow;
        re.screen = this->m_screen;
        this->InitRenderer(re);
        return 0;
    }
}