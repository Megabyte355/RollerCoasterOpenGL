#pragma once
#include "Model.h"

using namespace glm;

class BSpline :
    public Model
{
public:
    BSpline(void);
    ~BSpline(void);

    glm::vec3 GetNextPoint();
    virtual void Update(float dt);
	virtual void Draw();

    void Init();
    void AddPoint(glm::vec3 p);
    void SetDegree(int degree);
    void SetSpeed(float speed);

protected:
    std::vector<glm::vec3> points;
    virtual bool ParseLine(const std::vector<ci_string> &token);
    float BasisFunction(int i, int p, float t);

    vec4 BSplineF0(vec3 p1, vec3 p2, vec3 p3, vec3 p4, float t);
    vec4 BSplineF1(vec3 p1, vec3 p2, vec3 p3, vec3 p4, float t);
    vec4 BSplineF2(vec3 p1, vec3 p2, vec3 p3, vec3 p4, float t);
    std::vector<float> knots;

private:
    // n + 1 points, degree p
    int n;
    int p;
    bool initialized;

    float progress;
    float speed;

};
