// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva

#include <GLM/glm.hpp>
#include "Particle.h"

using namespace glm;

Particle::Particle()
{
}

Particle::Particle(float moveSpeed, vec4 normalizedDirection, float lifespan, float deceleration) {
    this->deceleration = deceleration;
    this->moveSpeed = moveSpeed;
    this->normalizedDirection = normalizedDirection;
    this->lifespan = lifespan;
}

void Particle::Update(float dt) {
    //moveSpeed += deceleration * dt;
    //mPosition += moveSpeed * dt * vec3(normalizedDirection);

    moveSpeed += -0.1f * dt;
    mPosition += moveSpeed * dt * vec3(normalizedDirection);

    mRotationAngleInDegrees += 90.0f * dt;
    lifespan -= dt;
}

bool Particle::isAlive() {
    return (this->lifespan > 0);
}

Particle::~Particle()
{
}
