#pragma once

using namespace glm;

#include "Model.h"

class RayCast
{
public:
	RayCast();
    static int Intersect3DTriangle(vec4 originPoint, vec4 directionVector, vec3 p1, vec3 p2, vec3 p3);
	~RayCast();

	struct CollisionResult
	{
		vec4 collisionPointWorld; //coordinates in world space where the collision actually occurred(good to know, I guess)
		vec4 collisionPointModel; //coordinates relative to the model where it's being hit (useful for decals)
		Model * model; //the model being hit by the collision
		vec4 normal; //the normal vector of the triangle being collided(this is SUPER IMPORTANT for decals)
	};

private:
	
};

