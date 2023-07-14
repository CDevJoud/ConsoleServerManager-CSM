#include "Panel.hpp"
namespace ugr
{
    VOID Panel::CreatePanel(Vector2i size)
    {
        this->m_vecBufferSize = size;
        this->m_Buffer = new CHAR_INFO[size.x * size.y];
        ZeroMemory(this->m_Buffer, 4 * size.x * size.y);
        this->re.buffer = this->m_Buffer;
        this->re.screen = size;
        this->InitRenderer(re);
    }

    VOID Panel::SetPosition(Vector2i pos)
    {
        this->m_vecPosition = pos;
    }

    VOID Panel::SetBorderChar(SHORT c)
    {
        this->m_n16BorderChar = c;
    }
    VOID Panel::SetBorderColor(SHORT color)
    {
        this->m_n16BorderColor = color;
    }

    VOID Panel::CreateMenuBar(BYTE sizex, SHORT c, SHORT color)
    {
        this->m_MenuBarProp.sizeX = sizex;
        this->m_MenuBarProp.surface = c;
        this->m_MenuBarProp.color = color;
    }

    VOID Panel::AddMenu(LPCWSTR menutitle, Menu* attachMenuto, SHORT col)
    {
        MenuButton tmp;
        tmp.menuTitle = menutitle;
        tmp.RedirectMenuBox = attachMenuto;
        tmp.MenuButtonColor = col;
        this->m_vecMenuButton.push_back(tmp);
    }

    VOID Panel::RenderPanel(Panel* p)
    {
        Vector2i p1(p->m_vecPosition);
        Vector2i p2(p->m_vecPosition + p->m_vecBufferSize);

        for (INT x = p1.x; x < p2.x; x++)
            for (INT y = p1.y; y < p2.y; y++)
            {
                INT py = (y - p1.y);
                INT px = (x - p1.x);
                auto surface = p->m_Buffer[py * p->m_vecBufferSize.x + px].Char.UnicodeChar;
                auto color = p->m_Buffer[py * p->m_vecBufferSize.x + px].Attributes;
                SetPixel(Vector2i(x, y), surface, color);
            }
        auto pos = p->m_vecPosition;
        auto size = p->m_vecBufferSize;
        auto color = p->m_n16BorderColor;
        auto title = p->m_Paneltitle;
        auto titlecol = p->m_PanelTitleColor;
        //Draw The Border
        this->RenderLine(Vector2i(pos.x - 1, pos.y - 1), Vector2i(pos.x + size.x - 1, pos.y - 1), 0x2500, color);

        this->RenderLine(Vector2i(pos.x - 1, pos.y - 1), Vector2i(pos.x - 1, pos.y + size.y - 1), 0x2502, color);

        this->RenderLine(Vector2i(pos.x, pos.y + size.y), Vector2i(pos.x + size.x, pos.y + size.y), 0x2500, color);

        this->RenderLine(Vector2i(pos.x + size.x, pos.y + size.y), Vector2i(pos.x + size.x, pos.y), 0x2502, color);
        //Set Corner style
        //Top
        SetPixel(Vector2i(pos.x - 1, pos.y - 1), 0x256D, color);

        //Right
        SetPixel(Vector2i(pos.x + size.x, pos.y - 1), 0x256E, color);

        //Left
        SetPixel(Vector2i(pos.x - 1, pos.y + size.y), 0x2570, color);

        //Bottom
        SetPixel(pos + size, 0x256F, color);

        this->RenderText(Vector2i(pos.x + (size.x / 2) - (lstrlenW(title) / 2), pos.y - 1), title, titlecol);
    }

    VOID Panel::SetTitle(LPCWSTR title, SHORT color)
    {
        this->m_Paneltitle = title;
        this->m_PanelTitleColor = color;
        
    }
    VOID Panel::Display()
    {
        //RenderMenuBar
        auto menusizex = this->m_MenuBarProp.sizeX;
        auto menusur = this->m_MenuBarProp.surface;
        auto menucol = this->m_MenuBarProp.color;

        this->RenderLine(Vector2i(0, 0), Vector2i(menusizex, 0), menusur, menucol);
        
        SHORT offsetX = 2;
        for (auto& i : this->m_vecMenuButton)
        {
            this->RenderText(Vector2i(offsetX, 0), i.menuTitle, i.MenuButtonColor);
            offsetX += lstrlenW(i.menuTitle) + 2;
        }
    }
}