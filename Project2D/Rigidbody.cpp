#pragma once
#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass) : PhysicsObject(shapeID)
{
	m_mass = mass;
	m_position = position;
	m_shapeID = shapeID;
	m_velocity = velocity;
	m_orientation = orientation;
}
void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_position += m_velocity * timeStep;
	applyForce(gravity * m_mass * timeStep);
}
void Rigidbody::applyForce(glm::vec2 force) 
{
	m_velocity = force / m_mass;
}
void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force) 
{
	actor2->applyForce(force);
	applyForce(-force);
}

glm::vec2 Rigidbody::setVelocity(glm::vec2 velocity)
{
	m_velocity = velocity; 
	return velocity;
}