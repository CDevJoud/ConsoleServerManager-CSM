#include "Renderer.hpp"
namespace ugr
{
    Renderer::Renderer(RenderElements re)
    {
        this->m_bufferScreen = re.buffer;
        this->m_handleConsole = re.hConsole;
        this->m_screen = re.screen;
        this->m_rectConsoleWindow = re.rectWin;
    }
	VOID Renderer::InitRenderer(RenderElements re)
    {
        this->m_bufferScreen = re.buffer;
        this->m_handleConsole = re.hConsole;
        this->m_screen = re.screen;
        this->m_rectConsoleWindow = re.rectWin;
    }
	VOID Renderer::RenderPixelPixel(BOOL sw)
	{
		this->RePP = sw;
	}
	VOID Renderer::SetRenderingCoolDown(DWORD millisecond)
	{
		this->millisecond = millisecond;
	}
	VOID Renderer::SetPixel(Vector2i c, SHORT sur, SHORT col)
    {
        if (c.x >= 0 && c.x < this->m_screen.x && c.y >= 0 && c.y < this->m_screen.y)
        {
            this->m_bufferScreen[c.y * this->m_screen.x + c.x].Char.UnicodeChar = sur;
            this->m_bufferScreen[c.y * this->m_screen.x + c.x].Attributes = col;
			if (RePP)
			{
				Sleep(this->millisecond);
				this->Display();
			}
        }
    }
	VOID Renderer::Fill(Vector2i p1, Vector2i p2, SHORT surface, SHORT color)
    {
        FindClip(p1);
        FindClip(p2);
        for (INT x = p1.x; x < p2.x; x++)
			for (INT y = p1.y; y < p2.y; y++)
				SetPixel(Vector2i(x, y), surface, color);
    }
	VOID Renderer::RenderLine(Vector2i p1, Vector2i p2, SHORT sur, SHORT col)
    {
		INT x1 = p1.x; INT x2 = p2.x; INT y1 = p1.y; INT y2 = p2.y;

		INT x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

		dx = x2 - x1; dy = y2 - y1;

		dx1 = abs(dx); dy1 = abs(dy);

		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = x1; y = y1; xe = x2;
			}
			else
			{
				x = x2; y = y2; xe = x1;
			}

			this->SetPixel(Vector2i(x, y), sur, col);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				this->SetPixel(Vector2i(x, y), sur, col);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = x1; y = y1; ye = y2;
			}
			else
			{
				x = x2; y = y2; ye = y1;
			}

			this->SetPixel(Vector2i(x, y), sur, col);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				this->SetPixel(Vector2i(x, y), sur, col);
			}
		}
    }
	VOID Renderer::RenderTriangle(Vector2i p1, Vector2i p2, Vector2i p3, SHORT sur, SHORT col)
	{
		RenderLine(p1, p2, sur, col);
		RenderLine(p2, p3, sur, col);
		RenderLine(p3, p1, sur, col);
	}
	VOID Renderer::RenderTriangle(FLOAT* p, SHORT sur, SHORT col)
	{
		Vector2i p1(p[0], p[1]);
		Vector2i p2(p[2], p[3]);
		Vector2i p3(p[4], p[5]);

		RenderTriangle(p1, p2, p3, sur, col);
	}
	VOID Renderer::RenderTriangle(VertexArray& p_Array, SHORT surface, SHORT col)
	{
		this->RenderTriangle(p_Array[0], p_Array[1], p_Array[2], surface, col);
		return VOID();
	}
	VOID Renderer::RasterizeTriangle(Vector2i p1, Vector2i p2, Vector2i p3, SHORT sur, SHORT col)
	{
		INT x1 = p1.x;
		INT y1 = p1.y;
		
		INT x2 = p2.x;
		INT y2 = p2.y;
		
		INT x3 = p3.x;
		INT y3 = p3.y;
		auto SWAP = [](INT& x, INT& y) { INT t = x; x = y; y = t; };
		auto drawline = [&](INT sx, INT ex, INT ny) { for (INT i = sx; i <= ex; i++) SetPixel(Vector2i(i, ny), sur, col); };

		INT t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		INT signx1, signx2, dx1, dy1, dx2, dy2;
		INT e1, e2;
		// Sort vertices
		if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }
		if (y1 > y3) { SWAP(y1, y3); SWAP(x1, x3); }
		if (y2 > y3) { SWAP(y2, y3); SWAP(x2, x3); }

		t1x = t2x = x1; y = y1;   // Starting poINTs
		dx1 = (INT)(x2 - x1); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (INT)(y2 - y1);

		dx2 = (INT)(x3 - x1); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (INT)(y3 - y1);

		if (dy1 > dx1) {   // swap values
			SWAP(dx1, dy1);
			changed1 = TRUE;
		}
		if (dy2 > dx2) {   // swap values
			SWAP(dy2, dx2);
			changed2 = TRUE;
		}

		e2 = (INT)(dx2 >> 1);
		// Flat top, just process the second half
		if (y1 == y2) goto next;
		e1 = (INT)(dx1 >> 1);

		for (INT i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;//t1x += signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
			// Move line
		next1:
			// process second line until y value is about to change
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;//t2x += signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);    // Draw line from min to max poINTs found on the y
										 // Now increase y
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;

		}
	next:
		// Second half
		dx1 = (INT)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (INT)(y3 - y2);
		t1x = x2;

		if (dy1 > dx1) {   // swap values
			SWAP(dy1, dx1);
			changed1 = TRUE;
		}
		else changed1 = FALSE;

		e1 = (INT)(dx1 >> 1);

		for (INT i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }//t1x += signx1;
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i < dx1) i++;
			}
		next3:
			// process second line until y value is about to change
			while (t2x != x3) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next4:

			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > y3) return;
		}
	}
	VOID Renderer::RasterizeTriangle(VertexArray& p_Array, SHORT surface, SHORT col)
	{
		this->RasterizeTriangle(p_Array[0], p_Array[1], p_Array[2], surface, col);
	}
	VOID Renderer::RenderCircle(Vector2i p1, INT radius, SHORT sur, SHORT col)
	{
		INT xc = p1.x;
		INT yc = p1.y;
		INT x = 0;
		INT y = radius;
		INT p = 3 - 2 * radius;
		if (!radius) return;

		while (y >= x) // only formulate 1/8 of circle
		{
			SetPixel(Vector2i(xc - x, yc - y), sur, col);//upper left left
			SetPixel(Vector2i(xc - y, yc - x), sur, col);//upper upper left
			SetPixel(Vector2i(xc + y, yc - x), sur, col);//upper upper right
			SetPixel(Vector2i(xc + x, yc - y), sur, col);//upper right right
			SetPixel(Vector2i(xc - x, yc + y), sur, col);//lower left left
			SetPixel(Vector2i(xc - y, yc + x), sur, col);//lower lower left
			SetPixel(Vector2i(xc + y, yc + x), sur, col);//lower lower right
			SetPixel(Vector2i(xc + x, yc + y), sur, col);//lower right right
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	}
	VOID Renderer::RasterizeCircle(Vector2i p1, INT r, SHORT sur, SHORT col)
	{
		INT yc = p1.y;
		INT xc = p1.x;
		// Taken from wikipedia
		INT x = 0;
		INT y = r;
		INT p = 3 - 2 * r;
		if (!r) return;

		auto drawline = [&](INT sx, INT ex, INT ny)
		{
			for (INT i = sx; i <= ex; i++)
				SetPixel(Vector2i(i, ny), sur, col);
		};

		while (y >= x)
		{
			// Modified to draw scan-lines instead of edges
			drawline(xc - x, xc + x, yc - y);
			drawline(xc - y, xc + y, yc - x);
			drawline(xc - x, xc + x, yc + y);
			drawline(xc - y, xc + y, yc + x);
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	}
	VOID Renderer::RenderQuad(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p4, SHORT sur, SHORT col)
	{
		this->RenderLine(p1, p2, sur, col);
		this->RenderLine(p2, p3, sur, col);
		this->RenderLine(p3, p4, sur, col);
		this->RenderLine(p4, p1, sur, col);
	}
	VOID Renderer::RasterizeQuad(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p4, SHORT sur, SHORT col)
	{
		this->RasterizeTriangle(p1, p2, p3, sur, col);
		this->RasterizeTriangle(p1, p4, p3, sur, col);
	}
	VOID Renderer::RenderQuad(Vector2i size, Vector2i pos, SHORT sur, SHORT col)
	{
		Vector2i p[4];
		p[0] = Vector2i(0, 0);
		p[1] = Vector2i(size.x, 0);
		p[2] = size;
		p[3] = Vector2i(0, size.y);

		this->RenderLine(p[0] + pos, p[1] + pos, sur, col);
		this->RenderLine(p[1] + pos, p[2] + pos, sur, col);
		this->RenderLine(p[2] + pos, p[3] + pos, sur, col);
		this->RenderLine(p[3] + pos, p[0] + pos, sur, col);
	}
	VOID Renderer::RasterizeQuad(Vector2i size, Vector2i pos, SHORT sur, SHORT col)
	{
		Vector2i p[4];
		p[0] = Vector2i(0, 0);
		p[1] = Vector2i(size.x, 0);
		p[2] = size;
		p[3] = Vector2i(0, size.y);

		this->Fill(p[0] + pos, p[2] + pos, sur, col);
	}
	VOID Renderer::RenderText(Vector2i pos,LPCWSTR str, SHORT color)
	{
		for (INT i = 0; i < lstrlenW(str); i++)
		{
			this->m_bufferScreen[pos.y * this->m_screen.x + pos.x + i].Char.UnicodeChar = str[i];
			this->m_bufferScreen[pos.y * this->m_screen.x + pos.x + i].Attributes = color;

			if (RePP)
			{
				Sleep(this->millisecond);
				this->Display();
			}
		}
	}
    VOID Renderer::FindClip(Vector2i& p)
    {
        if (p.x < 0) p.x = 0;
        if (p.x >= this->m_screen.x) p.x = this->m_screen.x;
        if (p.y < 0) p.y = 0;
        if (p.y >= this->m_screen.y) p.y = this->m_screen.y;
    }
	VOID Renderer::ClearScreen(SHORT sur, SHORT col)
	{
		this->Fill(ugr::Vector2i(0, 0), this->m_screen, sur, col);
	}
	VOID Renderer::Display()
    {
        WriteConsoleOutput(this->m_handleConsole, this->m_bufferScreen, { (short)this->m_screen.x, (short)this->m_screen.y }, { 0, 0 }, &this->m_rectConsoleWindow);
    }
}