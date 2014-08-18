// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva

#include <vector>
#include "Particle.h"
#include <GLM/glm.hpp>

using namespace glm;

#pragma once
class ParticleEmitter: public Model
{
public:
    ParticleEmitter();
    ParticleEmitter(vec4 point, vec4 normal); //To be used with ray casting
    ~ParticleEmitter();

    virtual void Update(float dt);
    virtual void Draw();
    
    virtual bool ParseLine(const std::vector<ci_string> &token);
    void GenerateParticles();

    bool isEmitterActive();
    std::vector<Particle*> GetParticles();
    static float RandomFloat(float min, float max);

protected:

    static std::vector<Particle*> particles;
    vec4 point;
    vec4 normal;
    bool isAlive;
};

