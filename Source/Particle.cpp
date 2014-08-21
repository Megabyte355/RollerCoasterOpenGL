// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva
//      Gary Chang

#include <GLM/glm.hpp>
#include "Particle.h"

using namespace glm;

Particle::Particle()
{
}

Particle::Particle(float moveSpeed, vec4 normalizedDirection, float lifespan, float deceleration, float rotationSpeed) {
    this->deceleration = deceleration;
    this->moveSpeed = moveSpeed;
    this->normalizedDirection = normalizedDirection;
    this->lifespan = lifespan;
    this->rotationSpeed = rotationSpeed;
}

void Particle::Update(float dt) {
    moveSpeed += deceleration * dt;
    mPosition += moveSpeed * dt * vec3(normalizedDirection);
    mRotationAngleInDegrees += rotationSpeed * dt;
    lifespan -= dt;
}

bool Particle::isAlive() {
    return (this->lifespan > 0);
}

Particle::~Particle()
{
}
