#pragma once
#include "../math/vec.hpp"
#include <algorithm>

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

double BoxSDF(const Vec2d& pos, const Vec2d& center, const double theta, const Vec2d& s)
{
	double sintheta = std::sin(theta);
	double costheta = std::cos(theta);
	Vec2d pos_obb = { std::abs(Vec2d(costheta, -sintheta) * (pos - center)), std::abs(Vec2d(sintheta, costheta) * (pos - center)) };
	Vec2d s_pos_obb = pos_obb - s;
	Vec2d a = { std::max<double>(s_pos_obb.x, 0.0), std::max<double>(s_pos_obb.y, 0.0) };
	return std::min<double>(std::max<double>(a.x, 0.0), 0.0) + a.Length();
}