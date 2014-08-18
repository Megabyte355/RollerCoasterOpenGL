// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva

#include "Model.h"
#include "Particle.h"
#include "LightModel.h"

using namespace glm;

#pragma once
class CubeParticle:public Particle
{

public:

    CubeParticle(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
    CubeParticle(float speed, vec4 normalizedDirection, float lifespan, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
    ~CubeParticle();
    
    void Init(vec3 size);
    void Draw();

    bool ParseLine(const std::vector<ci_string> &token);
    
};

