// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva

#include <GLM/glm.hpp>
#include "Particle.h"

using namespace glm;

Particle::Particle()
{

}

Particle::Particle(float moveSpeed, vec4 normalizedDirection, float lifespan) {
    this->moveSpeed = moveSpeed;
    this->normalizedDirection = normalizedDirection;
    this->lifespan = lifespan;
}

void Particle::Update(float dt) {
    mPosition += vec3(normalizedDirection) * dt * moveSpeed;
    lifespan -= dt;
}

bool Particle::isAlive() {
    return (this->lifespan > 0);
}

Particle::~Particle()
{
}
