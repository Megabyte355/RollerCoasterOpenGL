// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva
//      Gary Chang

#include "Model.h"

using namespace glm;

#pragma once
class Particle:public Model
{

public:
    Particle();
    Particle(float speed, vec4 normalizedDirection, float lifespan, float deceleration, float rotationSpeed);
    virtual void Init(vec3 size) = 0;
    virtual void Draw() = 0;
    void Update(float dt);

    bool isAlive();
    ~Particle();

protected:

    float deceleration;
    float moveSpeed;
    vec4 normalizedDirection;
    float lifespan;
    float rotationSpeed;
};

