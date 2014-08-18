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
    CubeParticle(vec4 point, float speed, vec4 normalizedDirection, float lifespan, float deceleration, float rotationSpeed, glm::vec3 colorA, glm::vec3 colorB, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
    ~CubeParticle();
    
    void Init(vec3 size);
    void Draw();

    bool ParseLine(const std::vector<ci_string> &token);
    
    glm::vec3 color1;
    glm::vec3 color2;
};

