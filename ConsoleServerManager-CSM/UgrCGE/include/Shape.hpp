#pragma once
#include "Vector.hpp"
#include <vector>
namespace ugr
{
	class Shape
	{
	public:
		const char* defShape = "NONE";
		std::vector<Vector2i> points;
		Vector2i pos;Vector2i size;
		short surface = 0;
		short color = 0;
	};
}
