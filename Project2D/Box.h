#pragma once
#include "Rigidbody.h"
#include "Gizmos.h"

class Box : public Rigidbody
{
public:
	Box(glm::vec2 extents, glm::vec2 position, glm::vec2 velocity, float mass, glm::vec4 colour);
	~Box();
	virtual void draw();
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	bool checkBoxCorners(Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);
	glm::vec2 getExtents() { return m_extents; }
	glm::vec2 getLocalX() { return m_localX; }
	glm::vec2 getLocalY() { return m_localY; }

	float getHeight() { return m_extents.y; }
	float getWidth() { return m_extents.x; }

protected:
	glm::vec2 m_extents;   // the halfedge lengths  
	glm::vec4 m_colour;

	// store the local x,y axes of the box based on its angle of rotation 
	glm::vec2 m_localX;
	glm::vec2 m_localY;

	//float m_height;
	//float m_width;
	glm::vec2 m_rotation;
};