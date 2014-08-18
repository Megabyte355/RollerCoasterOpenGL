// Contributors:
//      Gary Chang

#pragma once
#include "Model.h"

using namespace glm;

class BSpline : public Model
{
public:
    BSpline(void);
    ~BSpline(void);

    virtual void Update(float dt);
    virtual void Draw();

    void Init();
    glm::vec3 GetNextPoint();
    void AddPoint(glm::vec4 p);
    void SetSpeed(float speed);
    void SetClosedLoop(bool loop);
    void Reset();

    glm::vec4 GetVelocityUnitVector();
    bool LastPointReached();

protected:
    std::vector<glm::vec4> points;
    virtual bool ParseLine(const std::vector<ci_string> &token);

    vec4 BSplineF0(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, float t);
    vec4 BSplineF1(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, float t);
    vec4 BSplineF2(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, float t);

    int GetPointIndex(int i);

private:
    float speed;
    float t;
    int pointSetIndex;
	bool closedLoop;
    bool finished;
};
