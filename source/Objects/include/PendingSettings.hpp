#pragma once

#include <RmlUi/Core.h>

struct PendingSettings
{
	bool fullscreen = false;
	unsigned char circlePolygons = 8;
	int width = 1280;
	int height = 720;
	Rml::String circleResTex{ "8" };
	Rml::String resTex{ "1280 X 720" };
	Rml::String fullscreenTex{ "Fullscreen" };
};