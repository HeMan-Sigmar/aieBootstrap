#include "glm/glm.hpp"
#include <vector>
#pragma once

class PhysicsObject;

class PhysicsSense
{
public:
	PhysicsSense();
	~PhysicsSense();

	void addActer (PhysicsObject* object);
	void removeActer (PhysicsObject* object);
	void Update(float deltaTime);
	void Draw();

	void setGravity(const glm::vec2 gravity, );
	glm::vec2 getGravity();
	
	void setTimeStep();
	float getTimeStep();
private:

};