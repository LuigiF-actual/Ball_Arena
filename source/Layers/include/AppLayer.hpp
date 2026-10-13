#pragma once


#include <stdint.h>
#include <vector>
#include <ranges>
#include <print>

#include <raylib.h>

#include "Layer.hpp"

#include <CameraHandler.hpp>
#include <KineticCircle.hpp>
#include <QuadTree.hpp>
#include <Box.hpp>
#include <WindowEvents.hpp>
#include <WorldConfig.hpp>

class AppLayer : public Layer
{
public:
	AppLayer();
	~AppLayer() = default;

	void OnEvent(Event& event) override;

	void OnUpdate() override;
	void OnRender() override;


private:

	bool OnWindowResize(RenderTextureResize& event);

private:

	Vector2 m_RenderTexSize{ 1280.0f,720.0f };

	Box m_CameraArea{};
	
	CameraHandler m_Cam;

	DynamicQuadTreeContainer<KineticCircle> m_QuadTree;


};
