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
    float BasisFunction(int i, int p, float t);

    std::vector<float> knots;

private:

    // i: index of point
    // p: degree
    // x: progression

    //int n = points.size() - 1;
    //int d = n + 1;
    //int numKnots = n + d + 2;
    int n;
    int p;
    int numKnots;
    
};
