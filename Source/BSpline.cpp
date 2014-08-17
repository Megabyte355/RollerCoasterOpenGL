// Contributors:
//      Gary Chang

#include "BSpline.h"

using namespace glm;

BSpline::BSpline(void)
{
	Init();
}


BSpline::~BSpline(void)
{
}

void BSpline::Init()
{
	speed = 0.0f;
	pointSetIndex = 0;
	t = 0;
	closedLoop = true;
    finished = false;
}

vec3 BSpline::GetNextPoint()
{
    glm::vec4 p1(points[GetPointIndex(0)]);
    glm::vec4 p2(points[GetPointIndex(1)]);
    glm::vec4 p3(points[GetPointIndex(2)]);
    glm::vec4 p4(points[GetPointIndex(3)]);

    glm::vec4 nextPoint = BSplineF0(p1, p2, p3, p4, t);
    return glm::vec3(nextPoint.x, nextPoint.y, nextPoint.z);
}

void BSpline::Update(float dt)
{
    if (!finished)
    {
        glm::vec4 p1(points[GetPointIndex(0)]);
        glm::vec4 p2(points[GetPointIndex(1)]);
        glm::vec4 p3(points[GetPointIndex(2)]);
        glm::vec4 p4(points[GetPointIndex(3)]);

        float velocity = length(BSplineF1(p1, p2, p3, p4, t));
        t += (speed * dt) / velocity;
        if (t > 1.0f)
        {
            t = 0.0f;
            pointSetIndex++;
            if (pointSetIndex == points.size() && closedLoop)
            {
                pointSetIndex = 0;
            }
            finished = pointSetIndex == points.size() - 3 && !closedLoop;
        }
    }
}

void BSpline::Draw()
{
}

void BSpline::AddPoint(glm::vec4 p)
{
    points.push_back(p);
}

void BSpline::SetSpeed(float speed)
{
    this->speed = speed;
}

void BSpline::SetClosedLoop(bool loop)
{
	this->closedLoop = loop;
}

void BSpline::Reset()
{
    pointSetIndex = 0;
    t = 0.0f;
    finished = false;
}

glm::vec4 BSpline::GetVelocityUnitVector()
{
    glm::vec4 p1(points[GetPointIndex(0)]);
    glm::vec4 p2(points[GetPointIndex(1)]);
    glm::vec4 p3(points[GetPointIndex(2)]);
    glm::vec4 p4(points[GetPointIndex(3)]);
    return normalize(BSplineF1(p1, p2, p3, p4, t));
}

bool BSpline::LastPointReached()
{
    return finished;
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

	if (closedLoop)
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
	else
	{
		if (pointSetIndex >= points.size() - 3)
		{
			pointSetIndex = 0;
		}
		return pointSetIndex + i;
	}
}