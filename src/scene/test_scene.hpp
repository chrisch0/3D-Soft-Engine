#pragma once
#include <functional>
#include "../core/image.hpp"

void UVTest(Image* surface)
{
	for (int u = 0; u < surface->GetWidth(); ++u)
	{
		for (int v = 0; v < surface->GetHeight(); ++v)
		{
			unsigned char r = u * 255 / surface->GetWidth();
			unsigned char g = v * 255 / surface->GetHeight();
			surface->SetColorBGR(u, v, Color_255(r, g, 0, 0));
		}
	}
}
