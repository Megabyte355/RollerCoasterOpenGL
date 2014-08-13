#include "BSpline.h"

using namespace glm;

BSpline::BSpline(void)
{
    n = 0;
    p = 0;
    progress = 0.0f;
    speed = 0.0f;
    initialized = false;
    pointSetIndex = 0;
    t = 0;
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
    //n = points.size() - 1;
    //int m = n + p + 1;
    //int numKnots = m + 1;

    //for(int i = 0; i <= p; i++)
    //{
    //    knots.push_back(0.0f);
    //}

    //for(int i = 1; i <= n - p; i++)
    //{
    //    knots.push_back(i / (float)(n - p + 1));
    //}

    //for(int i = m - p; i <= m; i++)
    //{
    //    knots.push_back(1.0f);
    //}


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


    //if(!initialized)
    //{
    //    Init();
    //    initialized = true;
    //}

    //vec3 acc = vec3(0.0f, 0.0f, 0.0f);

    //for(int i = 0; i < points.size(); i++)
    //{
    //    acc += points[i] * BasisFunction(i, p, progress);
    //}
    //return acc;
    glm::vec4 p1(points[GetPointIndex(0)]);
    glm::vec4 p2(points[GetPointIndex(1)]);
    glm::vec4 p3(points[GetPointIndex(2)]);
    glm::vec4 p4(points[GetPointIndex(3)]);

    glm::vec4 nextPoint = BSplineF0(p1, p2, p3, p4, t);
    return glm::vec3(nextPoint.x, nextPoint.y, nextPoint.z);
}

void BSpline::Update(float dt)
{
    //progress = (speed * dt) / length(BSplineF1(points[0], points[1], points[2], points[3], progress));
    float velocity = length(BSplineF1(points[GetPointIndex(0)], points[GetPointIndex(1)], points[GetPointIndex(2)], points[GetPointIndex(3)], t));
    t += (speed * dt) / velocity;
    if (t > 1.0f)
    {
        t = 0.0f;
        pointSetIndex++;
        if (pointSetIndex == points.size())
        {
            pointSetIndex = 0;
        }
    }
    //if(progress > 1.0f)
    //{
    //    progress = 0.0f;
    //}
}

void BSpline::Draw()
{
}

void BSpline::AddPoint(glm::vec4 p)
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

// EXPERIMENT TO BE REMOVED
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

glm::vec4 BSpline::BSplineF0(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, float t)
{
    vec4 parametric(pow(t,3), pow(t,2), t, 1);
    mat4 coefficients(vec4(-1, 3, -3, 1), vec4(3, -6, 0, 4), vec4(-3, 3, 3, 1), vec4(1, 0, 0, 0));
    vec4 product = (1.0f / 6.0f) * parametric * coefficients;
    return product.x * p1 + product.y * p2 + product.z * p3 + product.w * p4;
}

glm::vec4 BSpline::BSplineF1(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, float t)
{
    vec4 parametric(3 * pow(t, 2), 2 * t, 1, 0);
    mat4 coefficients(vec4(-1, 3, -3, 1), vec4(3, -6, 0, 4), vec4(-3, 3, 3, 1), vec4(1, 0, 0, 0));
    vec4 product = (1.0f / 6.0f) * parametric * coefficients;
    return product.x * p1 + product.y * p2 + product.z * p3 + product.w * p4;

}

glm::vec4 BSpline::BSplineF2(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, float t)
{
    vec4 parametric(6*t, 2, 0, 0);
    mat4 coefficients(vec4(-1, 3, -3, 1), vec4(3, -6, 0, 4), vec4(-3, 3, 3, 1), vec4(1, 0, 0, 0));
    vec4 product = (1.0f / 6.0f) * parametric * coefficients;
    return product.x * p1 + product.y * p2 + product.z * p3 + product.w * p4;
}

int BSpline::GetPointIndex(int i)
{
    // i = 0,1,2,3
    // Compute wraparound
    if (pointSetIndex == points.size() - 3)
    {
        if (i == 3)
        {
            return 0;
        }
        else if (i == 2)
        {
            return points.size() - 1;
        }
        else if (i == 1)
        {
            return points.size() - 2;
        }
        else
        {
            return points.size() - 3;
        }
    }
    else if (pointSetIndex == points.size() - 2)
    {
        if (i == 3)
        {
            return 1;
        }
        else if (i == 2)
        {
            return 0;
        }
        else if (i == 1)
        {
            return points.size() - 1;
        }
        else
        {
            return points.size() - 2;
        }

    }
    else if (pointSetIndex == points.size() - 1)
    {
        if (i == 3)
        {
            return 2;
        }
        else if (i == 2)
        {
            return 1;
        }
        else if (i == 1)
        {
            return 0;
        }
        else
        {
            return points.size() - 1;
        }
    }
    else
    {
        return pointSetIndex + i;
    }
}