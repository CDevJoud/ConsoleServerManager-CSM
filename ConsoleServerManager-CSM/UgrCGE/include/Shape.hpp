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
#include "Vector.hpp"
#include <vector>
#include <Windows.h>
namespace ugr
{
	typedef std::vector<Vector2i> VertexArray;
	class Shape
	{
	public:
		VOID SetShapeType(LPCSTR shapeType);
		LPCSTR GetShapeType() CONST;

		VOID SetPosition(Vector2i pos);
		VOID SetPosition(INT x, INT y);
		Vector2i GetPosition() CONST;

		VOID SetSize(Vector2i size);
		VOID SetSize(INT x, INT y);
		Vector2i GetSize() CONST;

		VOID SetVertexArray(VertexArray& VA);
		VOID AddVertex(Vector2i vertex);

		VertexArray& GetVertexArray();
		Vector2i GetVertex(INT vertex) CONST;

		VOID SetColor(SHORT color);
		VOID SetChar(SHORT c);

		SHORT GetColor() CONST;
		SHORT GetChar() CONST;
	public:

		const char* defShape = "NONE";
		std::vector<Vector2i> points;
		Vector2i pos;Vector2i size;
		short surface = 0;
		short color = 0;
	private:
		LPCSTR m_strShapeType = "NONE";
		VertexArray m_VertexArray;
		Vector2i m_vecPosition;
		Vector2i m_vecSize;
		SHORT m_n16Surface = 0x2588;
		SHORT m_n16Color = 0x0F;
	};
}
