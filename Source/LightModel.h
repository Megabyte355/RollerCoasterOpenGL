// Contributors:
//      Gary Chang
// 	    Oleksandr Dymov

#pragma once

#include "Model.h"
#include <GL/glew.h>

class LightModel : public Model
{
public:
    LightModel();
    LightModel(Model * parent);
    virtual ~LightModel(void);

    virtual void Update(float dt);
    virtual void Draw();

    void SetShaderConstants(float ka, float kd, float ks, float n);

    glm::vec3 lightColor;
    glm::vec4 lightPosition;
    float lightKc;
    float lightKl;
    float lightKq;

    // For the sun postion relative to center of the plane	
    float sunAngle;

protected:
    virtual bool ParseLine(const std::vector<ci_string> &token);
    virtual void Init();

private:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };
};
