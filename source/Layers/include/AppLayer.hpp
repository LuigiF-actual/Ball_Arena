#pragma once


#include <stdint.h>
#include <vector>
#include <ranges>
#include <print>

#include <raylib.h>


#include "Layer.hpp"

class AppLayer : public Layer
{
public:
	AppLayer();
	~AppLayer() = default;

	void OnUpdate() override;
	void OnRender() override;

private:

	Rectangle myRec{ 100.0f, 100.0f, 200.0f, 200.0f};

};
