#include "BSpline.h"

using namespace glm;

BSpline::BSpline(void)
{
    // EXPERIMENT TO BE REMOVED
    //points.push_back(vec3(3.0f, -1.0f, 0.0f));
    //points.push_back(vec3(3.0f, -3.0f, 0.0f));
    //points.push_back(vec3(3.0f, -1.0f, 0.0f));
    //points.push_back(vec3(3.0f, 1.0f, 0.0f));
    //points.push_back(vec3(3.0f, -1.0f, 0.0f));

    //points.push_back(vec3(0.0f, 0.0f, 0.0f));
    //points.push_back(vec3(3.0f, 0.0f, 0.0f));
    //points.push_back(vec3(3.0f, 3.0f, 0.0f));
    //points.push_back(vec3(0.0f, 3.0f, 0.0f));
    //points.push_back(vec3(0.0f, 0.0f, 2.0f));
    //points.push_back(vec3(3.0f, 0.0f, 2.0f));
    //points.push_back(vec3(3.0f, 3.0f, 2.0f));
    //points.push_back(vec3(0.0f, 3.0f, 2.0f));
    //points.push_back(vec3(0.0f, 0.0f, 4.0f));
    //points.push_back(vec3(3.0f, 0.0f, 4.0f));

    //points.push_back(vec3(0.0f, 0.0f, 0.0f));
    //points.push_back(vec3(3.0f, 0.0f, 0.0f));
    //points.push_back(vec3(3.0f, 3.0f, 0.0f));
    //points.push_back(vec3(0.0f, 3.0f, 0.0f));
    //points.push_back(vec3(0.0f, 0.0f, 0.0f));
    //points.push_back(vec3(3.0f, 0.0f, 0.0f));
    //points.push_back(vec3(0.0f, 3.0f, 0.0f));
    //points.push_back(vec3(3.0f, 3.0f, 0.0f));
    //points.push_back(vec3(3.0f, 0.0f, 0.0f));
    //points.push_back(vec3(0.0f, 0.0f, 0.0f));


    // Cool path from OneNote
    //points.push_back(vec3(0.0f, 0.0f, 0.0f));
    //points.push_back(vec3(2.0f, 0.0f, 0.0f));
    //points.push_back(vec3(4.0f, 1.0f, 0.0f));
    //points.push_back(vec3(6.0f, 2.0f, 0.0f));
    //points.push_back(vec3(8.0f, 3.0f, 0.0f));
    //points.push_back(vec3(7.0f, 5.0f, 0.0f));
    //points.push_back(vec3(5.0f, 6.0f, 0.0f));
    //points.push_back(vec3(3.0f, 5.0f, 0.0f));
    //points.push_back(vec3(2.0f, 4.0f, 0.0f));
    //points.push_back(vec3(0.0f, 3.0f, 0.0f));
    //points.push_back(vec3(-2.0f, 1.0f, 0.0f));
    //points.push_back(vec3(0.0f, 0.0f, 0.0f));


    points.push_back(vec3(0.0f, 0.0f, 0.0f));
    points.push_back(vec3(5.0f, 0.0f, 10.0f));
    points.push_back(vec3(10.0f, 0.0f, 0.0f));
    // n + 1 control points
    // points.size() = n + 1
    n = points.size() - 1;

    // try with this degree for now (degree is chosen)
    //p = n - 1;
    p = 3;

    // m + 1 knots, m = n + p + 1
    numKnots = n + p + 2;
    //int clampedKnots = p + 1;
    float knotIncrement = 1.0f / (numKnots - 1);

    for(int i = 0; i < numKnots; i++)
    {
        knots.push_back(knotIncrement * i);
    }
    //knots.push_back(0.00f);
    //knots.push_back(0.01f);
    //knots.push_back(0.02f);
    //knots.push_back(0.03f);
    //knots.push_back(0.14f);
    //knots.push_back(0.28f);
    //knots.push_back(0.42f);
    //knots.push_back(0.57f);
    //knots.push_back(0.71f);
    //knots.push_back(0.85f);
    //knots.push_back(0.97f);
    //knots.push_back(0.98f);
    //knots.push_back(0.99f);
    //knots.push_back(1.0f);

    // a set of n+1 control points, a knot vector of m+1 knots, and a degree p

    // m = n + p + 1
    // degree: p = m - n - 1

    // degree p
    // n + 1 control points
    // supply n + p + 2 knots! (m + 1 knots!!!)


    // 5 control points (n = 4)
    // degree 4 (p = 4)
    // need 10 knots!
}


BSpline::~BSpline(void)
{
}

vec3 BSpline::GetPoint(float t)
{
    //float b0;
    //float b1;
    //float b2;
    //float b3;
    //float b4;

    //if(0 <= t && t < 1)
    //{
    //    b0 = (1-t)*(1-t);
    //    b1 = 2*((t-1)*t);
    //    b2 = t*t;
    //    b3 = 0;
    //    b4 = 0;
    //}
    //else if (1 <=t && t <=2)
    //{
    //    b0 = 0;
    //    b1 = 0;
    //    b2 = (2-t)*(2-t);
    //    b3 = 2*(2-t)*(t-1);
    //    b4 = (t-1)*(t-1);
    //}

    //return points[0]*b0 + points[1]*b1 + points[2]*b2 + points[3]*b3 + points[4]*b4;
    
    vec3 acc = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < points.size(); i++)
    {
        acc += points[i] * BasisFunction(i, p, t);
    }
    return acc;
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

float BSpline::BasisFunction(int i, int p, float t)
{
    if(p == 0)
    {
        if(knots[i] <= t && t < knots[i + 1] && knots[i] < knots[i+1])
        {
            return 1.0f;
        }
        return 0.0f;
    }
    else
    {
        float slope = (t - knots[i])/(knots[i+p] - knots[i]) * BasisFunction(i, p - 1, t);
        float intercept = (knots[i + p + 1] - t)/(knots[i + p + 1] - knots[i + 1]) * BasisFunction(i + 1, p - 1, t);
        return (slope) + (intercept);
    }
}