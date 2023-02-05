#include "glm/glm.hpp"
#include <vector>
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
		float getTotalEnergy();
		static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	private:
		glm::vec2 m_gravity;
		float m_timeStep;
		std::vector<PhysicsObject*> m_actors;
	};