#include "Panel.hpp"
namespace ugr
{
    VOID Panel::CreatePanel(Vector2i size)
    {
        this->m_vecBufferSize = size;
        this->m_Buffer = new CHAR_INFO[size.x * size.y];
        ZeroMemory(this->m_Buffer, 4 * size.x * size.y);
        /*for (INT x = 0; x < size.x; x++)
            for (INT y = 0; y < size.y; y++)
            {
                this->m_Buffer[y * size.x + x].Char.UnicodeChar = 0x2588;
                this->m_Buffer[y * size.x + x].Attributes = 0x0A;
            }*/
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
    VOID Panel::AddMenuToBar(LPCWSTR t, Vector2i off, SHORT col)
    {
        this->RenderText(off, t, col);
    }
}