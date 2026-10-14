#pragma once


#include <stdint.h>
#include <vector>
#include <ranges>
#include <print>

#include <raylib.h>
#include <raymath.h>

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

	void updateMousePos();
	void checkForClicks();
	void updateMouseDrag();
	void launchCircle(KineticCircle& circle_);
	void updatePhysics();
	void transferVelocity(KineticCircle& circle1, KineticCircle& circle2);

private:

	bool m_IsDragging;

	DynamicQuadTreeContainer<KineticCircle>::iterator m_ActiveHandler;

	Vector2 m_WorldMousePos{0.0f};
	Vector2 m_RenderTexSize{ 1280.0f,720.0f };

	std::list < DynamicQuadTreeContainer<KineticCircle>::iterator > m_ActiveObjs;

	Box m_CameraArea{};
	Box m_ClickArea{ 0.0f,0.0f,10.0f,10.0f };
	
	CameraHandler m_Cam;


	DynamicQuadTreeContainer<KineticCircle> m_QuadTree;



};
