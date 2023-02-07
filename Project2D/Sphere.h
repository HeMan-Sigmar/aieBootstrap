#pragma once
#include "Rigidbody.h"

class Sphere : public Rigidbody
{
public:
    Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
    ~Sphere();

    virtual void draw();

    float getRadius() { return m_radius; }
    glm::vec4 getColour() { return m_colour; }
    glm::vec2 getNormal() { return m_normal; }

protected:
    float m_radius;
    glm::vec4 m_colour;
    glm::vec2 m_normal;
};