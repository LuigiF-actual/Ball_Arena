#pragma once


#include <stdint.h>
#include <vector>
#include <ranges>
#include <print>

#include <raylib.h>


#include "Layer.hpp"

#include <CameraHandler.hpp>

class AppLayer : public Layer
{
public:
	AppLayer();
	~AppLayer() = default;

	void OnUpdate() override;
	void OnRender() override;

private:

	CameraHandler m_Cam;

};
