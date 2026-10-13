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

	CameraHandler m_Cam;
	Box m_CameraArea{ 0.0f,0.0f,720.0f,720.0f };

	DynamicQuadTreeContainer<KineticCircle> m_QuadTree;

	KineticCircle m_Cir{ 45.0f,{200.0f,200.0f} };

};
