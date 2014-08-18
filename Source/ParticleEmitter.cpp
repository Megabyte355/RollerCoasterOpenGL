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
}

ParticleEmitter::ParticleEmitter(vec4 point, vec4 normal) {
    this->point = point;
    this->normal = normal;
}

void ParticleEmitter::GenerateParticles() {

    /* initialize random seed: */
    srand(time(NULL));
    /* generate secret number between 1 and 10: */
    
    int randomParticleNumber = rand() % 10 + 200;
    std::cout << "randomParticleNumber :" << randomParticleNumber << std::endl;

    vec4 particleDirection = normal;

    for (unsigned int i = 0; i < randomParticleNumber; i++) {
        int randomAxis = rand() % 3;
        float randomAngleinDegrees = RandomFloat(-90, 90);
        float randomSpeed = RandomFloat(10, 20);
        float randomLifespan = RandomFloat(1, 3);
        float randomDeceleration = - RandomFloat(0, 1);

        float randomX = RandomFloat(-10, 10);
        float randomY = RandomFloat(-10, 10);
        float randomZ = RandomFloat(-10, 10);

        vec4 particleDirection = normalize(vec4(randomX, randomY, randomZ, 0.0f));

        CubeParticle* cp = new CubeParticle(point, 10, particleDirection, randomLifespan, randomDeceleration);
        cp->SetLightSource(mLightSource);
        particles.push_back(cp);
    }
}

bool ParticleEmitter::isEmitterActive() {
    return isAlive;
}

void ParticleEmitter::Update(float dt) {
    for (std::vector<Particle*>::iterator it = particles.begin(); it < particles.end();)
    {
        if (*it != nullptr){
            (*it)->Update(dt);
            if (!(*it)->isAlive()) {
                delete *it;
                it = particles.erase(it);
            }
            else
            {
                it++;
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
    for (std::vector<Particle*>::iterator it = particles.begin(); it < particles.end(); it++)
    {
        delete *it;
    }
    particles.clear();
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
