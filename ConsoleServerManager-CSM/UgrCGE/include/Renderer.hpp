#pragma once
#include <Windows.h>
#include <iostream>
#include "Shape.hpp"

namespace ugr
{
	
	struct RenderElements
	{
		CHAR_INFO* buffer = NULL;
		HANDLE hConsole = NULL;
		Vector2i screen = Vector2i(0, 0);
		SMALL_RECT rectWin = { 0, 0, 0, 0 };
	};
	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(RenderElements RE);

		void InitRenderer(RenderElements RE);

		//Rendering Functions
		VOID RenderPixelPixel(BOOL sw);
		VOID SetRenderingCoolDown(DWORD millisecond);
		VOID SetPixel(Vector2i cordinates, SHORT surface = 0x2588, SHORT col = 0x000F);
		

		VOID RenderLine(Vector2i p1, Vector2i p2, SHORT surface = 0x2588, SHORT col = 0x000F);

		VOID RenderTriangle(Vector2i p1, Vector2i p2, Vector2i p3, SHORT surface = 0x2588, SHORT col = 0x000F);
		VOID RenderTriangle(FLOAT* p_Array, SHORT surface = 0x2588, SHORT col = 0x000F);
		VOID RenderTriangle(VertexArray& p_Array, SHORT surface = 0x2588, SHORT col = 0x000F);

		VOID RasterizeTriangle(Vector2i p1, Vector2i p2, Vector2i p3, SHORT surface = 0x2588, SHORT col = 0x000F);
		VOID RasterizeTriangle(VertexArray& p_Array, SHORT surface = 0x2588, SHORT col = 0x000F);

		VOID RenderCircle(Vector2i p1, INT radius, SHORT surface = 0x2588, SHORT col = 0x000F);
		VOID RasterizeCircle(Vector2i p1, INT radius, SHORT surface = 0x2588, SHORT col = 0x00F);

		VOID RenderQuad(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p4, SHORT surface = 0x2588, SHORT col = 0x000F);
		VOID RasterizeQuad(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p4, SHORT surface = 0x2588, SHORT col = 0x000F);
		VOID RenderQuad(Vector2i size, Vector2i pos, SHORT surface = 0x2588, SHORT col = 0x000F);
		VOID RasterizeQuad(Vector2i size, Vector2i pos, SHORT surface = 0x2588, SHORT col = 0x000F);
		VOID RenderText(Vector2i pos,LPCWSTR str, SHORT color = 0x000F);


		//Caclulating Functions

		VOID FindClip(Vector2i& p);

		VOID ClearScreen(SHORT surface = 0x2588, SHORT color = 0x0000);
		VOID Display();
	private:
		void Fill(Vector2i p1, Vector2i p2, SHORT surface = 0x2588, SHORT col = 0x000F);
		CHAR_INFO* m_bufferScreen = NULL;
		Vector2i m_screen = Vector2i(0, 0);
		HANDLE m_handleConsole = NULL;
		SMALL_RECT m_rectConsoleWindow;
		BOOL RePP = FALSE;
		DWORD millisecond = 0;
	};
}
