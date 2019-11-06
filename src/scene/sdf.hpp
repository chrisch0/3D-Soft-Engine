#pragma once
#include "../math/vec.hpp"

double CircleSDF(const Vec2d& pos, const Vec2d& o, double r)
{
	return (pos - o).Length() - r;
}

double PlaneSDF(const Vec2d& pos, const Vec2d& p, const Vec2d& n)
{
	return (pos - p) * n;
}

double CapsuleSDF(const Vec2d& pos, const Vec2d& a, const Vec2d& b, double r)
{
	Vec2d vapos = pos - a;
	Vec2d vbpos = pos - b;
	Vec2d vab = b - a;
	Vec2d t = (vapos * vab) * (vbpos * vab) < 0.0 ? a + vab * (vab * vapos) / vab.Length() : (vapos.Length() < vbpos.Length() ? a : b);
	return (t - pos).Length() - r;
}