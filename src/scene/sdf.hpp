#pragma once
#include "../math/vec.hpp"

double CircleSDF(Vec2d pos, Vec2d o, double r)
{
	return (pos - o).Length() - r;
}