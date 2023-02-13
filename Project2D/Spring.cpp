#pragma once
#include "Spring.h"

void Spring::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	// get the world coordinates of the ends of the springs 
	glm::vec2 p1 = getContact1();
	glm::vec2 p2 = getContact2();

	float length = glm::distance(p1, p2);
	glm::vec2 direction = glm::normalize(p2 - p1);

	// apply damping 
	glm::vec2 relativeVelocity = m_body2->getVelocity() - m_body1->getVelocity();

	// F = -kX - bv 
	glm::vec2 force = direction * m_springCoefficient * (m_restLength - length) -
		m_damping * relativeVelocity;

	m_body1->applyForce(-force * timeStep, p1 - m_body1->getPosition());
	m_body2->applyForce(force * timeStep, p2 - m_body2->getPosition());
}

glm::vec2 Spring::getContact1()
{
	return m_body1 ? m_body1->toWorld(m_contact1) : m_contact1;
}