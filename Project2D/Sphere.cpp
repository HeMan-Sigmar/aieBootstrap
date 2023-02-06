#pragma once
#include "Sphere.h"
#include "Gizmos.h"
Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : Rigidbody(SPHERE, position, velocity, 0, mass)
{
    m_radius = radius;
    m_colour = colour;
    m_position = position;
    m_mass = mass;
    m_velocity = velocity;
}

void Sphere::draw()
{
    //aie::Gizmos::add2DCircle(m_position, m_radius, 30, m_colour);

    glm::vec2 end = glm::vec2(std::cos(m_orientation), std::sin(m_orientation)) *
        m_radius;

    aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
    aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));
}