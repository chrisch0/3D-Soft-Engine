#pragma once
#include <random>
#include <vector>
#include <cmath>
#include <iostream>
#include "../core/image.hpp"
#include "sdf.hpp"

static const double pi = 3.1415926535897932384626433832795;
static const double tau = 6.283185307179586476925286766559;

static std::default_random_engine r_engine;
static std::uniform_real_distribution<double> u_double(0, 1);

Vec2d ObjectUnion(const Vec2d& o1, const Vec2d& o2)
{
	return o1.x < o2.x ? o1 : o2;
}

Vec2d ObjectIntersect(const Vec2d& o1, const Vec2d& o2)
{
	Vec2d r = o1.x < o2.x ? o1 : o2;
	r.x = o1.x < o2.x ? o2.x : o1.x;
	return r;
}

Vec2d ObjectSubtract(const Vec2d& o1, const Vec2d& o2)
{
	Vec2d r = o1;
	r.x = o1.x > -o2.x ? o1.x : -o2.x;
	return r;
}

// Return { signed distance, light intensity}
Vec2d Scene(const Vec2d& pos)
{
	/*Vec2d c1 = { CircleSDF(pos, Vec2d(0.3, 0.3), 0.1), 2.0 };
	Vec2d c2 = { CircleSDF(pos, Vec2d(0.3, 0.7), 0.05), 0.8 };
	Vec2d c3 = { CircleSDF(pos, Vec2d(0.7, 0.5), 0.1), 0.1 };
	return ObjectUnion(c1, ObjectUnion(c2, c3));*/

	/*Vec2d c1 = { CircleSDF(pos, Vec2d(0.4, 0.5), 0.2), 1.0 };
	Vec2d c2 = { CircleSDF(pos, Vec2d(0.6, 0.5), 0.2), 0.8 };
	//return ObjectUnion(c1, c2);
	//return ObjectIntersect(c1, c2);
	//return ObjectSubtract(c1, c2);
	return ObjectSubtract(c2, c1);*/

	Vec2d capsule1 = { CapsuleSDF(pos, Vec2d(0.4, 0.4), Vec2d(0.6, 0.6), 0.1), 1.0 };
	return capsule1;
}

double Trace(const Vec2d& pos, const Vec2d& dir)
{
	double t = 0.0f;
	Vec2d circle_1(0.5, 0.5);
	for (int i = 0; i < 10 && t < 2.0f; ++i)
	{
		Vec2d scene = Scene(pos + dir * t);
		if (scene.x < 1e-6)
			return scene.y;
		t += scene.x;
	}
	return 0.0f;
}

double Sample(double u, double v)
{
	double sum = 0.0;
	double sample_times = 64.0;
	std::random_device r;
	r_engine.seed(r());
	for (int i = 0; i < sample_times; ++i)
	{
		// Uniform sampling
		//double rand = tau * u_double(r_engine);

		// Stratified sampling
		//double rand = tau * i / sample_times;

		// Jittered sampling
		double rand = tau * (i + u_double(r_engine)) / sample_times;
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