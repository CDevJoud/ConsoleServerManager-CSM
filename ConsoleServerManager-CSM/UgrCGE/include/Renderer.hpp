#pragma once
#include <Windows.h>
#include <iostream>
#include "Vector.hpp"

namespace ugr
{
	struct RenderElements
	{
		CHAR_INFO* buffer = nullptr;
		HANDLE hConsole = nullptr;
		Vector2i screen = Vector2i(0, 0);
		SMALL_RECT rectWin;
	};
	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(RenderElements RE);

		void InitRenderer(RenderElements RE);

		//Rendering Functions
		void RenderPixelPixel(bool sw);
		void SetRenderingCoolDown(DWORD millisecond);
		void SetPixel(Vector2i cordinates, SHORT surface = 0x2588, SHORT col = 0x000F);
		

		void RenderLine(Vector2i p1, Vector2i p2, SHORT surface = 0x2588, SHORT col = 0x000F);

		void RenderTriangle(Vector2i p1, Vector2i p2, Vector2i p3, SHORT surface = 0x2588, SHORT col = 0x000F);
		void RenderTriangle(FLOAT* p_Array, SHORT surface = 0x2588, SHORT col = 0x000F);

		void RasterizeTriangle(Vector2i p1, Vector2i p2, Vector2i p3, SHORT surface = 0x2588, SHORT col = 0x000F);
		
		void RenderCircle(Vector2i p1, INT radius, SHORT surface = 0x2588, SHORT col = 0x000F);
		void RasterizeCircle(Vector2i p1, INT radius, SHORT surface = 0x2588, SHORT col = 0x00F);

		void RenderQuad(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p4, SHORT surface = 0x2588, SHORT col = 0x000F);
		void RasterizeQuad(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p4, SHORT surface = 0x2588, SHORT col = 0x000F);
		void RenderQuad(Vector2i size, Vector2i pos, SHORT surface = 0x2588, SHORT col = 0x000F);
		void RasterizeQuad(Vector2i size, Vector2i pos, SHORT surface = 0x2588, SHORT col = 0x000F);
		void RenderText(Vector2i pos,LPCWSTR str, SHORT color = 0x000F);


		//Caclulating Functions

		void FindClip(Vector2i& p);

		void ClearScreen(SHORT surface = 0x2588, SHORT color = 0x0000);
		void Display();
	private:
		void Fill(Vector2i p1, Vector2i p2, SHORT surface = 0x2588, SHORT col = 0x000F);
		CHAR_INFO* m_bufferScreen = nullptr;
		Vector2i m_screen = Vector2i(0, 0);
		HANDLE m_handleConsole = nullptr;
		SMALL_RECT m_rectConsoleWindow;
		bool RePP = false;
		DWORD millisecond = 0;
	};
}
