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

    points.push_back(vec3(0.0f, -1.0f, 0.0f));
    points.push_back(vec3(1.0f, -3.0f, 0.0f));
    points.push_back(vec3(2.0f, -1.0f, 0.0f));
    points.push_back(vec3(3.0f, 1.0f, 0.0f));
    points.push_back(vec3(4.0f, -1.0f, 0.0f));

    //int size = points.size();
    //float knotIncrement = 1.0f / (size - 1);

    //for(int i = 0; i < size; i++)
    //{
    //    knots.push_back(knotIncrement * i);
    //}
    n = points.size() - 1;
    d = n + 1;
    numKnots = n + d + 2;

    float knotIncrement = 1.0f / (numKnots - 1);

    for(int i = 0; i < numKnots; i++)
    {
        knots.push_back(knotIncrement * i);
    }
    

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
        acc += points[i] * BasisFunction(i, d, t);
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
    // EXPERIMENT
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
        return ((t - knots[i])/(knots[i+p] - knots[i]) * BasisFunction(i, p - 1, t)) + 
            ((knots[i + p + 1] - t)/(knots[i+p+1] - knots[i+1])*BasisFunction(i + 1, p - 1, t));
    }
}