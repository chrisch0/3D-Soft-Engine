#pragma once
#include <random>
#include <vector>
#include <cmath>
#include "../core/image.hpp"
#include "sdf.hpp"

static const double pi = 3.1415926535897932384626433832795;
static const double tau = 6.283185307179586476925286766559;

static std::default_random_engine r_engine;
static std::uniform_real_distribution<double> u_double(0, 1);

double Trace(Vec2d pos, Vec2d dir)
{
	double t = 0.0f;
	Vec2d circle_1(0.5, 0.5);
	for (int i = 0; i < 10 && t < 2.0f; ++i)
	{
		double sd = CircleSDF(pos + dir * t, circle_1, 0.1);
		if (sd < 1e-6)
			return 2.0f;
		t += sd;
	}
	return 0.0f;
}

double Sample(int u, int v)
{
	double sum = 0.0;
	int sample_times = 64;
	std::random_device r;
	r_engine.seed(r());
	for (int i = 0; i < sample_times; ++i)
	{
		double rand = u_double(r_engine);
		sum += Trace(Vec2d((double)u, (double)v), Vec2d(std::cos(rand), std::sin(rand)));
	}
	return sum;
}

void FirstLight(Image* surface)
{
	for (int u = 0; u < surface->GetWidth(); ++u)
	{
		for (int v = 0; v < surface->GetHeight(); ++v)
		{
			auto sam = Sample(u, v);
			Color baseColor(1.0, 0.7, 0.8, 1.0);
			surface->SetColorBGR(u, v, baseColor * sam);
		}
	}
}