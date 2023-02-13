#include "glm/glm.hpp"
#include <vector>
#include "Box.h"
#pragma once

class PhysicsObject;

	class PhysicsScene
	{
	public:
		PhysicsScene();
		~PhysicsScene();

		void AddActor(PhysicsObject* actor);
		void RemoveActor(PhysicsObject* actor);
		void Update(float deltaTime);
		void Draw();

		void SetGravity(const glm::vec2 gravity) { m_gravity = gravity; }
		glm::vec2 GetGravity() const { return m_gravity; }

		void SetTimeStep(const float timeStep) { m_timeStep = timeStep; }
		float GetTimeStep() const { return m_timeStep; }

		void checkForCollision();

		static bool plane2Plane(PhysicsObject*, PhysicsObject*);
		static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
		static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
		static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
		static bool sphere2Box (PhysicsObject*, PhysicsObject*);
		static bool box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
		static bool box2Box(PhysicsObject* obj1, PhysicsObject* obj2);
		static bool box2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
		static bool plane2Box(PhysicsObject* obj1, PhysicsObject* obj2);

		float getTotalEnergy();
		void ApplyContactForces(Rigidbody* body1, Rigidbody* body2, glm::vec2 norm, float pen);
	private:
		glm::vec2 m_gravity;
		float m_timeStep;
		std::vector<PhysicsObject*> m_actors;
	};