#pragma once
#include "Rigidbody.h"
#include "PhysicsScene.h"
#include <iostream>

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

	/*m_orientation += m_angularVelocity * timeStep;*/
	
}
void Rigidbody::applyForce(glm::vec2 force) 
{
	m_velocity += force / m_mass;

	//m_velocity += force / getMass();
	//m_angularVelocity += (force.y * pos.x - force.x * pos.y) / getMoment();
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
float Rigidbody::getKineticEnergy()
{
	float v;
	float m = 0;
	return (0.5 * m) * (pow(v, 2));
}
void Rigidbody::resolveCollision(Rigidbody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;
	//glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
		((1 / m_mass) + (1 / actor2->getMass()));

	glm::vec2 force = normal * j;

	float kePre = getKineticEnergy() + actor2->getKineticEnergy();

	applyForceToActor(actor2, -force);

	float kePost = getKineticEnergy() + actor2->getKineticEnergy();

	float deltaKE = kePost - kePre;
	if (deltaKE > kePost * 0.01f)
		std::cout << "Kinetic Energy discrepancy greater than 1% detected!!";


	//// find the vector between their centres, or use the provided direction 
 //// of force, and make sure it's normalised 
	//glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal :
	//	actor2->m_position - m_position);
	//// get the vector perpendicular to the collision normal 
	//glm::vec2  perp(normal.y, -normal.x);

	//// determine the total velocity of the contact points for the two objects,  
 //  // for both linear and rotational     

	// // 'r' is the radius from axis to application of force 
	//float r1 = glm::dot(contact - m_position, -perp);
	//float r2 = glm::dot(contact - actor2->m_position, perp);
	//// velocity of the contact point on this object  
	//float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
	//// velocity of contact point on actor2 
	//float v2 = glm::dot(actor2->m_velocity, normal) +
	//	r2 * actor2->m_angularVelocity;
	//if (v1 > v2) // they're moving closer 
	//{
	//	// calculate the effective mass at contact point for each object 
	//	// ie how much the contact point will move due to the force applied. 
	//	float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
	//	float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2 * r2) / actor2->m_moment);

	//	float elasticity = 1;

	//	glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 /
	//		(mass1 + mass2) * (v1 - v2) * normal;

	//	//apply equal and opposite forces 
	//	applyForce(-force, contact - m_position);
	//	actor2->applyForce(force, contact - actor2->m_position);
}
float Rigidbody::getPotentialEnergy()
{
	PhysicsScene getGrav;
	return -getMass() * glm::dot(getGrav.GetGravity(), getPosition());
}