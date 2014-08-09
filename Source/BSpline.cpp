#include "BSpline.h"

using namespace glm;

BSpline::BSpline(void)
{
    // EXPERIMENT TO BE REMOVED
    points.push_back(vec3(3.0f, -1.0f, 0.0f));
    points.push_back(vec3(3.0f, -3.0f, 0.0f));
    points.push_back(vec3(3.0f, -1.0f, 0.0f));
    points.push_back(vec3(3.0f, 1.0f, 0.0f));
    points.push_back(vec3(3.0f, -1.0f, 0.0f));
}


BSpline::~BSpline(void)
{
}

vec3 BSpline::GetPoint(float t)
{
    float b0;
    float b1;
    float b2;
    float b3;
    float b4;

    if(0 <= t && t < 1)
    {
        b0 = (1-t)*(1-t);
        b1 = 2*((t-1)*t);
        b2 = t*t;
        b3 = 0;
        b4 = 0;
    }
    else if (1 <=t && t <=2)
    {
        b0 = 0;
        b1 = 0;
        b2 = (2-t)*(2-t);
        b3 = 2*(2-t)*(t-1);
        b4 = (t-1)*(t-1);
    }

    return points[0]*b0 + points[1]*b1 + points[2]*b2 + points[3]*b3 + points[4]*b4;
}

void BSpline::Update(float dt)
{
}

void BSpline::Draw()
{
}

bool BSpline::ParseLine(const std::vector<ci_string> &token)
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