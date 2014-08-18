// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva
//      Gary Chang

#include <GLM/glm.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

#include "ParticleEmitter.h"
#include "Particle.h"
#include "CubeParticle.h"

// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva
//      Gary Chang

std::vector<Particle*> ParticleEmitter::particles;

ParticleEmitter::ParticleEmitter(){
    Init();
}

ParticleEmitter::ParticleEmitter(vec4 normal) {
    this->normal = normal;
    Init();
}

void ParticleEmitter::Init() {

    /* initialize random seed: */
    srand(time(NULL));
    /* generate secret number between 1 and 10: */
    
    int randomParticleNumber = rand() % 10 + 10;
    std::cout << "randomParticleNumber :" << randomParticleNumber << std::endl;

    vec4 particleDirection = normal;

    for (unsigned int i = 0; i < randomParticleNumber; i++) {
        int randomAxis = rand() % 3;
        float randomAngleinDegrees = RandomFloat(-90, 90);
        float randomSpeed = RandomFloat(0, 10);
        float randomLifespan = RandomFloat(3000, 10000);

        float randomX = RandomFloat(-10, 10);
        float randomY = RandomFloat(-10, 10);
        float randomZ = RandomFloat(-10, 10);

        std::cout << "randomAxis :" << randomAxis << std::endl;
        std::cout << "randomAngleinDegrees :" << randomAngleinDegrees << std::endl;
        std::cout << "randomSpeed :" << randomSpeed << std::endl;
        std::cout << "randomLifespan :" << randomLifespan << std::endl << std::endl << std::endl;

        vec4 particleDirection(randomX, randomY, randomZ, 0.0f);

        CubeParticle* cp = new CubeParticle(randomSpeed, particleDirection, randomLifespan);
        particles.push_back(cp);
    }
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
