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