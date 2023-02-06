#include "Plane.h"
#include "glm/glm.hpp"
#include "Gizmos.h"
#include "Rigidbody.h"
#include <iostream>

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(ShapeType::PLANE) {
    m_distanceToOrigin = distance;
    m_normal = normal;
}
Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::draw()
{
    glm::vec4 m_colour = glm::vec4 (1, 0,0, 1);
    float lineSegmentLength = 300;
    glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
    // easy to rotate normal through 90 degrees around z
    glm::vec2 parallel(m_normal.y, -m_normal.x);
    glm::vec4 colourFade = m_colour;
    colourFade.a = 0;
    glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
    glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
    aie::Gizmos::add2DLine(start, end, m_colour);
    aie::Gizmos::add2DTri(start, end, start - m_normal * 10.0f, m_colour, m_colour, colourFade);
    aie::Gizmos::add2DTri(end, end - m_normal * 10.0f, start - m_normal * 10.0f, m_colour, colourFade, colourFade);
}

void Plane::resolveCollision(Rigidbody* actor2, glm::vec2 contact)
{
    
    glm::vec2 relativeVelocity = actor2->getVelocity();
    float e = actor2->getElasticity();
    float j = glm::dot(-(1.0f + e) * (relativeVelocity), m_normal) /  ((1.f / actor2->getMass()));

    glm::vec2 force = m_normal * j;
    actor2->applyForce(force, contact - actor2->getPosition());
//
//    glm::vec2 vRel = actor2->getVelocity();
//    float e = actor2->getElasticity();
//    float j = glm::dot(-(1 + e) * (vRel), m_normal) / (1 / actor2->getMass());
//
//    vec2 force = m_normal * j;
 /*   actor2->applyForce(force, contact - actor2->getPosition());*/
}


