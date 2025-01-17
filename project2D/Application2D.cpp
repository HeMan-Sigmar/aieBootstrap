#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm/ext.hpp"
#include "Gizmos.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

Application2D::Application2D()
{

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	//m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_timer = 0;

	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetTimeStep(0.01f);
	m_physicsScene->SetGravity(glm::vec2(0,0));

	Sphere* ball1;
	Sphere* ball2;
	Sphere* ball3;
	Sphere* ball4;
	Sphere* ball5;
	Sphere* ball6;
	Sphere* ball7;
	ball1 = new Sphere(glm::vec2(1, 0), glm::vec2(100, 3), 2.f, 2, glm::vec4(1, 0, 0, 1));
	ball2 = new Sphere(glm::vec2(10, 0), glm::vec2(10, 13), 2.f, 2, glm::vec4(0, 1, 0, 1));
	ball3 = new Sphere(glm::vec2(5, 0), glm::vec2(10, -5), 2.f, 2, glm::vec4(0, 1, 0, 1));
	ball4 = new Sphere(glm::vec2(2, 0), glm::vec2(10, 5), 2.f, 2, glm::vec4(0, 1, 0, 1));
	ball5 = new Sphere(glm::vec2(-6, 0), glm::vec2(10, 23), 2.f, 2, glm::vec4(0, 1, 0, 1));
	ball6 = new Sphere(glm::vec2(7, 0), glm::vec2(10, 23), 2.f, 2, glm::vec4(0, 1, 0, 1));
	ball7 = new Sphere(glm::vec2(6, 0), glm::vec2(10, 23), 2.f, 2, glm::vec4(0, 0, 1, 1));

	Plane* plane1 = new Plane(glm::vec2(0, 1), -40);
	Plane* plane2 = new Plane(glm::vec2(0, -1), -40);
	Plane* plane3 = new Plane(glm::vec2(1, 0), -40);
	Plane* plane4 = new Plane(glm::vec2(-1, 0), -40);

	//Box* box1;
	//Box* box2;
	//Box* box3;
	//box1 = new Box(glm::vec2(2, 2), glm::vec2(0,-13), glm::vec2 (10,0), glm::vec2(2,10), 2.f, glm::vec4(1, 0, 0, 1));
	//box2 = new Box(glm::vec2(2, 2), glm::vec2(6,-4), glm::vec2 (10,0), glm::vec2(2, 10), 2.f, glm::vec4 (0, 0, 1, 1));
	//box3 = new Box(glm::vec2(2, 2), glm::vec2(36,-20), glm::vec2 (10,0), glm::vec2(2, 10), 2.f, glm::vec4 (0, 1, 1, 1));



	float angle = atan2(ball1->getPosition().y - ball2->getPosition().y, ball1->getPosition().x - ball2->getPosition().x);
	float inDegrees = angle * 180.0f / 3.141f;

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(ball3);
	m_physicsScene->AddActor(ball4);
	m_physicsScene->AddActor(ball5);
	m_physicsScene->AddActor(ball6);
	m_physicsScene->AddActor(ball7);

	m_physicsScene->AddActor(plane1);
	m_physicsScene->AddActor(plane2);
	m_physicsScene->AddActor(plane3);
	m_physicsScene->AddActor(plane4);

	//m_physicsScene->AddActor(box1);
	//m_physicsScene->AddActor(box2);
	//m_physicsScene->AddActor(box3);

	ball1->applyForce(glm::vec2(100, 0), glm::vec2(0,0));
	ball2->applyForce(glm::vec2(100, 0), glm::vec2(0,0));
	ball3->applyForce(glm::vec2(100, 0), glm::vec2(0,0));
	ball4->applyForce(glm::vec2(100,0), glm::vec2(0,0));
	ball5->applyForce(glm::vec2(100, 0), glm::vec2(0,0));
	ball6->applyForce(glm::vec2(100, 0), glm::vec2(0,0));
	ball7->applyForce(glm::vec2(100, 0), glm::vec2(0,0));

	//box1->applyForce(glm::vec2(50, 0), glm::vec2(0,0));
	//box2->applyForce(glm::vec2(50, 0), glm::vec2(0,0));
	//box3->applyForce(glm::vec2(50, 0), glm::vec2(0,0));



	return true;

}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	//m_physicsScene->SetTimeStep(0.01f);

	//// Update the camera position using the arrow keys
	//float camPosX;
	//float camPosY;
	//m_2dRenderer->getCameraPos(camPosX, camPosY);

	//if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	//	camPosY += 500.0f * deltaTime;

	//if (input->isKeyDown(aie::INPUT_KEY_UP))
	//	camPosY -= 500.0f * deltaTime;

	//if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	//	camPosX -= 500.0f * deltaTime;

	//if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	//	camPosX += 500.0f * deltaTime;

	//m_2dRenderer->setCameraPos(camPosX, camPosY);

	aie::Gizmos::clear();

	m_physicsScene->Update(deltaTime);


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	//// wipe the screen to the background colour
	//clearScreen();

	//// begin drawing sprites
	//m_2dRenderer->begin();

	//// demonstrate animation
	//m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	//// demonstrate spinning sprite
	//m_2dRenderer->setUVRect(0,0,1,1);
	//m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	//// draw a thin line
	//m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	//// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	//// draw a rotating red box
	//m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	//// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	//
	//// output some text, uses the last used colour
	//char fps[32];
	//sprintf_s(fps, 32, "FPS: %i", getFPS());
	//m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	//m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	//// done drawing sprites
	//m_2dRenderer->end();

		// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_physicsScene->Draw();
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}