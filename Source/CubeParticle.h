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
    CubeParticle();
    CubeParticle(float speed, vec4 normalizedDirection, float lifespan, int scale);
    void Init(vec3 size);
    void Draw();
    ~CubeParticle();

};

