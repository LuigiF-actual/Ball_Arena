#pragma once


namespace config
{
	constexpr float worldArea = 50'000.0f;
	constexpr size_t circleAmmount = 10'000;
	constexpr size_t circleResolution = 8;

	constexpr float initialResX = 1280;
	constexpr float initialResY = 720;

	constexpr float minCircleRadius = 10.0f;
	constexpr float maxCircleRadius = 100.0f;

	constexpr float minCamZoom = 0.125f;
	constexpr float maxCamZoom = 256.0f;
	
	constexpr float launchMultiplier = 2.0f;
	constexpr float friction = 300.0f;

	constexpr float mouseSearchSize = 10.0f;
}