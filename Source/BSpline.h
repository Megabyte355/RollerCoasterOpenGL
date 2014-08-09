#pragma once
#include "Model.h"
class BSpline :
    public Model
{
public:
    BSpline(void);
    ~BSpline(void);

    glm::vec3 GetPoint(float t);
    virtual void Update(float dt);
	virtual void Draw();

protected:
    std::vector<glm::vec3> points;
    virtual bool ParseLine(const std::vector<ci_string> &token);
};

