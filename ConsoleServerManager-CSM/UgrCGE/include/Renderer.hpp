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
		VOID SetPixel(Vector2i cordinates, SHORT surface = 0x2588, BYTE col = 0x0F);
		

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
		VOID RenderText(Vector2i pos,LPCSTR  str, SHORT color = 0x000F);

		//Caclulating Functions

		VOID FindClip(Vector2i& p);

		VOID ClearScreen(SHORT surface = 0x2588, SHORT color = 0x0000);
		void Fill(Vector2i p1, Vector2i p2, SHORT surface = 0x2588, SHORT col = 0x000F);

	private:
		CHAR_INFO* m_bufferScreen = NULL;
		Vector2i m_screen = Vector2i(0, 0);
		HANDLE m_handleConsole = NULL;
		SMALL_RECT m_rectConsoleWindow;
		BOOL RePP = FALSE;
		DWORD millisecond = 0;
	};
}
