#pragma once

using namespace glm;

#include "Model.h"

class RayCast
{
public:
	RayCast();
	bool LinePlaneIntersection(vec4 originPoint, vec4 directionVector, vec4 p1, vec4 p2, vec4 p3);
	~RayCast();

private:
	struct CollisionResult
	{
		vec4 collisionPointWorld; //coordinates in world space where the collision actually occurred(good to know, I guess)
		vec4 collisionModel; //coordinates relative to the model where it's being hit (useful for decals)
		Model * model; //the model being hit by the collision
		vec4 normal; //the normal vector of the triangle being collided(this is SUPER IMPORTANT for decals)
	};
};

