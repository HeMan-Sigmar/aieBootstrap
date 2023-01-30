#include "glm/glm.hpp"
#include <vector>
#pragma once

class PhysicsObject;

class PhysicsSense
{
public:
	PhysicsSense();
	~PhysicsSense();

	void AddActer (PhysicsObject* actor);
	void RemoveActer (PhysicsObject* actor);
	void Update(float deltaTime);
	void Draw();

	void SetGravity(const glm::vec2 gravity) { m_gravity = gravity;}
	glm::vec2 GetGravity() const {return m_gravity;}
	
	void SetTimeStep(const float timeStep) { m_timeStep = timeStep;}
	float GetTimeStep() const { return m_timeStep; }
private:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject> m_actor;
};