// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva
//      Gary Chang

#include <GLM/glm.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

#include"ParticleEmitter.h"
#include "Particle.h"

// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva

std::vector<Particle*> ParticleEmitter::particles;

ParticleEmitter::ParticleEmitter()
{
}

ParticleEmitter::ParticleEmitter(vec4 position, vec4 normal) {
    mPosition = vec3(position);
    this->normal = normal;
    Init();
}

void ParticleEmitter::Init() {

    /* initialize random seed: */
    srand(time(NULL));
    /* generate secret number between 1 and 10: */
    int randomAxis = rand() % 3;
    //float randomAngleinDegrees = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / MAX_RANDOM_ANGLE)) - 90;
    float randomAngleinDegrees = RandomFloat(-90, 90);
    
    float randomSpeed = RandomFloat(0, 10);
    float randomLifespan = RandomFloat(3000, 10000);

    std::cout << "randomAxis :" << randomAxis;
    std::cout << "randomAngleinDegrees :" << randomAngleinDegrees;
    std::cout << "randomSpeed :" << randomSpeed;
    std::cout << "randomLifespan :" << randomLifespan;

    vec4 particleDirection = normal;

    //switch (randomAxis)
    //{
    //case 0 :
    //    particleDirection.x = 
    //default:
    //    break;
    //}


}

void ParticleEmitter::checkParticlesLife() {

}

void ParticleEmitter::Update(float dt) {
    for each (Particle* p in particles)
    {
        if (p != nullptr){
            p->Update(dt);
            if (!p->isAlive()) {
                p = nullptr;
                delete p;
            }
        }
    }
}

void ParticleEmitter::Draw() {
    for each (Particle* p in particles)
    {
        if (p != nullptr){
            p->Draw();
        }
    }
}

ParticleEmitter::~ParticleEmitter()
{
}

bool ParticleEmitter::ParseLine(const std::vector<ci_string> &token)
{
    if (token.empty())
    {
        return true;
    }
    else
    {
        return Model::ParseLine(token);
    }
}

float ParticleEmitter::RandomFloat(float min, float max) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}
