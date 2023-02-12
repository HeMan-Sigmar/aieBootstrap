#pragma once
#include "PhysicsObject.h"
#include "glm/glm.hpp"

enum ShapeType {
    PLANE = 0,
    SPHERE,
    BOX,
};
const int SHAPE_COUNT = 3;
    class PhysicsObject
    {
    protected:
        PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

    public:
        virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
        virtual void draw() = 0;
        virtual void resetPosition() {};
        int getShapeID() { return m_shapeID;}
        int getEnergy() { return 0; }
    protected:
        ShapeType m_shapeID;
    };