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

double Sample(double u, double v)
{
	double sum = 0.0;
	double sample_times = 16.0;
	//std::random_device r;
	//r_engine.seed(r());
	for (int i = 0; i < sample_times; ++i)
	{
		//double rand = u_double(r_engine);
		double rand = tau * std::rand() / RAND_MAX;
		sum += Trace(Vec2d(u, v), Vec2d(std::cos(rand), std::sin(rand)));
	}
	return sum / sample_times;
}

void FirstLight(Image* surface)
{
	for (int w = 0; w < surface->GetWidth(); ++w)
	{
		for (int h = 0; h < surface->GetHeight(); ++h)
		{
			double u = (double)w / surface->GetWidth();
			double v = (double)h / surface->GetHeight();
			auto sam = Sample(u, v);
			Color_255 baseColor;
			baseColor.x = baseColor.y = baseColor.z = sam * 255;
			baseColor.w = 255;
			surface->SetColorBGR(w, h, baseColor);
			//unsigned char r = u * 255 / surface->GetWidth();
			//unsigned char g = v * 255 / surface->GetHeight();
			//surface->SetColorBGR(u, v, Color(r, g, 0, 0));
		}
	}
}