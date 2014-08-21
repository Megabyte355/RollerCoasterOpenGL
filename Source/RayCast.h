// Contributors:
//      Gary Chang
//      Kevin Silva

#pragma once

using namespace glm;

#include "Model.h"

class RayCast
{
public:
    struct CollisionResult
    {
        vec4 collisionPointWorld; //coordinates in world space where the collision actually occurred(good to know, I guess)
        Model * model; //the model being hit by the collision
        vec4 normal; //the normal vector of the triangle being collided(this is SUPER IMPORTANT for decals)
        bool collision;
    };
    
    RayCast();
    static CollisionResult IntersectBoundingBoxes(vec4 originPoint, vec4 directionVector);
    static CollisionResult Intersect3DTriangle(vec4 originPoint, vec4 directionVector, vec3 p1, vec3 p2, vec3 p3, Model* model);
	~RayCast();

private:
	
};

