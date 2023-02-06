#pragma once
#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "Plane.h"


    PhysicsScene::PhysicsScene()
    {
        m_timeStep = 0.01f;
        m_gravity = glm::vec2(0, 1);
    }
    PhysicsScene::~PhysicsScene()
    {
        for (auto pActor : m_actors)
        {
            delete pActor;
        }
    }
    void PhysicsScene::AddActor(PhysicsObject* actor)
    {
        m_actors.push_back(actor);
    }
    void PhysicsScene::RemoveActor(PhysicsObject* actor)
    {
        m_actors.erase(std::remove(m_actors.begin(), m_actors.end(), actor), m_actors.end());
    }

    // function pointer array for doing our collisions
    typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

    static fn collisionFunctionArray[] =
    {
        PhysicsScene::plane2Plane,     PhysicsScene::plane2Sphere,
        PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,
    };

    void PhysicsScene::Update(float dt)
    {
        // update physics at a fixed time step

        static float accumulatedTime = 0.0f;
        accumulatedTime += dt;

        while (accumulatedTime >= m_timeStep)
        {
            for (auto pActor : m_actors)
            {
                pActor->fixedUpdate(m_gravity, m_timeStep);
            }

            accumulatedTime -= m_timeStep;

            // check for collisions (ideally you'd want to have some sort of 
        // scene management in place)
            int actorCount = m_actors.size();

            // need to check for collisions against all objects except this one.
            for (int outer = 0; outer < actorCount - 1; outer++)
            {
                for (int inner = outer + 1; inner < actorCount; inner++)
                {
                    PhysicsObject* object1 = m_actors[outer];
                    PhysicsObject* object2 = m_actors[inner];

                    int shapeId1 = object1->getShapeID();
                    int shapeId2 = object2->getShapeID();

                    // using function pointers
                    int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
                    fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
                    if (collisionFunctionPtr != nullptr)
                    {
                        // did a collision occur?
                        collisionFunctionPtr(object1, object2);
                    }
                }
            }
        }
    }

    void PhysicsScene::Draw()
    {
        for (auto pActor : m_actors) {
            pActor->draw();
        }
    }

    bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
    {
        // try to cast objects to sphere and sphere
        Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
        Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

        // if we are successful then test for collision
        if (sphere1 != nullptr && sphere2 != nullptr)
        {
            if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) < sphere1->getRadius() + sphere2->getRadius())
            {
                sphere1->resolveCollision(sphere2, 0.5f * (sphere1->getPosition() + sphere2->getPosition()), );
            }
        }
        //sphere1->resolveCollision(sphere2, 0.5f * (sphere1->getPosition() + sphere2->getPosition()));
        return false;
    }

    bool PhysicsScene::plane2Plane(PhysicsObject*, PhysicsObject*)
    {
        return false;
    }

    bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
    {
        // reverse the order of arguments, as obj1 is the plane and obj2 is the sphere
        Plane* plane1 = dynamic_cast<Plane*>(obj1);
        Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
        return sphere2Plane(obj2, obj1);
    }

    bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
    {
        Sphere* sphere = dynamic_cast<Sphere*>(obj1);
        Plane* plane = dynamic_cast<Plane*>(obj2);
        glm::vec2 collisionNormal = plane->getNormal();
        glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
        //if we are successful then test for collision
        if (sphere != nullptr && plane != nullptr)
        {
            glm::vec2 collisionNormal = plane->getNormal();
            float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

            float intersection = sphere->getRadius() - sphereToPlane;
            float velocityOutOfPlane = glm::dot(sphere->getVelocity(), plane->getNormal());
            if (intersection > 0 && velocityOutOfPlane < 0)
            {
                //set sphere velocity to zero here
                plane->resolveCollision(sphere, contact);
                return true;
            }
        }
        return false;
    }
    float PhysicsScene::getTotalEnergy()
    {
        float total = 0;
        for (auto it = m_actors.begin(); it != m_actors.end(); it++)
        {
            PhysicsObject* obj = *it;
            total += obj->getEnergy();
        }
        return total;
    }