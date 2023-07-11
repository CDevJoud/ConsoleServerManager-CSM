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
