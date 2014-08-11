#include "BSpline.h"

using namespace glm;

BSpline::BSpline(void)
{
    n = 0;
    p = 0;
    progress = 0.0f;
    speed = 0.0f;
    initialized = false;
}


BSpline::~BSpline(void)
{
}

void BSpline::Init()
{
    // Condition: Set of n+1 control points, a knot vector of m+1 knots, and a degree p
    // Degree: p = m - n - 1

    // n + 1 control points
    // m + 1 knots, m = n + p + 1
    // Need to supply n + p + 2 knots (m + 1 knots minimum)

    // Constants
    n = points.size() - 1;
    int m = n + p + 1;
    int numKnots = m + 1;

    for(int i = 0; i <= p; i++)
    {
        knots.push_back(0.0f);
    }

    for(int i = 1; i <= n - p; i++)
    {
        knots.push_back(i / (float)(n - p + 1));
    }
    //knots.push_back(0.166666667);
    //knots.push_back(0.333333333);
    //knots.push_back(0.5);
    //knots.push_back(0.666666667);
    //knots.push_back(0.833333333);

    for(int i = m - p; i <= m; i++)
    {
        knots.push_back(1.0f);
    }
    //for(int j = 0; j <= m; j++)
    //{
    //    if(j <= p)
    //    {
    //        knots.push_back(0.0f);
    //    }
    //    else if (j >= m - p - 1)
    //    {
    //        knots.push_back(1.0f);
    //    }
    //    else
    //    {
    //        knots.push_back(j / (n - p + 1));
    //    }

    //}


//knots.push_back(0.0f);
//knots.push_back(0.083333333f);
//knots.push_back(0.166666667f);
//knots.push_back(0.25f);
//knots.push_back(0.333333333f);
//knots.push_back(0.416666667f);
//knots.push_back(0.5f);
//knots.push_back(0.583333333f);
//knots.push_back(0.666666667f); 
//knots.push_back(0.75f);
//knots.push_back(0.833333333f);
//knots.push_back(0.916666667f);
//knots.push_back(1.0f);

    //float knotIncrement = 1.0f / (numKnots - 1);

    //for(int i = 0; i < numKnots; i++)
    //{
    //    knots.push_back(knotIncrement * i);
    //}

    //int x = 0;
}

vec3 BSpline::GetNextPoint()
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
    if(!initialized)
    {
        Init();
        initialized = true;
    }

    vec3 acc = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < points.size(); i++)
    {
        acc += points[i] * BasisFunction(i, p, progress);
    }
    return acc;
}

void BSpline::Update(float dt)
{
    progress += speed * dt;
    if(progress > 1.0f)
    {
        progress = 0.0f;
    }
}

void BSpline::Draw()
{
}

void BSpline::AddPoint(glm::vec3 p)
{
    points.push_back(p);
}

void BSpline::SetDegree(int degree)
{
    p = degree;
}

void BSpline::SetSpeed(float speed)
{
    this->speed = speed;
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
        float term1 = 0.0f;
        if(abs(knots[i + p] - knots[i]) > 0.000001)
        {
            term1 = (t - knots[i])/(knots[i + p] - knots[i]) * BasisFunction(i, p - 1, t);
        }

        float term2 = 0.0f;
        if(abs(knots[i + p + 1] - knots[i + 1]) > 0.000001)
        {
            term2 = (knots[i + p + 1] - t)/(knots[i + p + 1] - knots[i + 1]) * BasisFunction(i + 1, p - 1, t);
        }
        return term1 + term2;
    }
}