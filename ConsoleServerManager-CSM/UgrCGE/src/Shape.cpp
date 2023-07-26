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

#include "Shape.hpp"
namespace ugr
{
	VOID Shape::SetShapeType(LPCSTR ST)
	{
		this->m_strShapeType = ST;
	}

	LPCSTR Shape::GetShapeType() const
	{
		return this->m_strShapeType;
	}

	VOID Shape::SetPosition(Vector2i pos)
	{
		this->m_vecPosition = pos;
	}

	VOID Shape::SetPosition(INT X, INT Y)
	{
		this->m_vecPosition = Vector2i(X, Y);
	}

	Vector2i Shape::GetPosition() const
	{
		return this->m_vecPosition;
	}
	VOID Shape::SetSize(Vector2i size)
	{
		this->m_vecSize = size;
	}
	VOID Shape::SetSize(INT X, INT Y)
	{
		this->m_vecSize = Vector2i(X, Y);
	}
	Vector2i Shape::GetSize() const
	{
		return this->m_vecSize;
	}
	VOID Shape::SetVertexArray(VertexArray& VA)
	{
		this->m_VertexArray = VA;
	}
	VOID Shape::AddVertex(Vector2i vertex)
	{
		this->m_VertexArray.push_back(vertex);
	}
	VertexArray& Shape::GetVertexArray()
	{
		return this->m_VertexArray;
	}
	Vector2i Shape::GetVertex(INT I) CONST
	{
		return this->m_VertexArray[I];
	}
	VOID Shape::SetColor(SHORT color)
	{
		this->m_n16Color = color;
	}
	VOID Shape::SetChar(SHORT c)
	{
		this->m_n16Surface = c;
	}
	SHORT Shape::GetColor() const
	{
		return this->m_n16Color;
	}
	SHORT Shape::GetChar() const
	{
		return this->m_n16Surface;
	}
}