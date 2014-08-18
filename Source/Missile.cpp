//
// Contribution by Alin
//

#include "Missile.h"
#include "CubeModel.h"
#include "TankModel.h"
#include "BSpline.h"
#include "World.h"

using namespace glm;
using namespace std;
#include "glm/ext.hpp"

int st;
std::vector<CubeModel*> container;
TankModel* tk;

Missile::Missile(TankModel* t)
{
	tk = t;
	Init();
}


Missile::~Missile(void)
{
	container.clear();
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		delete *it;
	}
	container.clear();
}

void Missile::Init()
{
	st = 0;	
}

void Missile::Add(vec3 position)
{
	CubeModel* cube = new CubeModel(this);
	cube->SetPosition(position);
	container.push_back(cube);

}

void Missile::Update(float dt)
{

		for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
		{
			BSpline* s = dynamic_cast<BSpline*>((*it)->GetBSpline());
			if (s != nullptr)
			{
				(*it)->SetPosition((*it)->GetBSpline()->GetPosition() + (*it)->GetBSpline()->GetNextPoint());

				(*it)->GetBSpline()->Update(dt);
				Trajectory();
			}
		}

}

void Missile::Trajectory()
{

	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		glm::vec3 startPos = (*it)->GetPosition();
		glm::vec3 endPos = tk->GetPosition();

		BSpline* s = dynamic_cast<BSpline*>((*it)->GetBSpline());
		if (s != nullptr)
		{
			(*it)->GetBSpline()->AddPoint(glm::vec4(startPos, 1.0f));
			(*it)->GetBSpline()->AddPoint(glm::vec4(startPos.x - 1.0f, startPos.y - 3.0f, startPos.z - 4.0f, 1.0f));
			(*it)->GetBSpline()->AddPoint(glm::vec4(endPos.x + 1.0f, endPos.y + 1.0f, endPos.z + 2.0f, 1.0f));
			(*it)->GetBSpline()->AddPoint(glm::vec4(endPos, 1.0f));
			(*it)->GetBSpline()->SetSpeed(5.0f);
			(*it)->GetBSpline()->SetClosedLoop(false);
		}
		else{
			BSpline* sp = new BSpline();
			sp->AddPoint(glm::vec4(startPos, 1.0f));
			sp->AddPoint(glm::vec4(startPos.x - 1.0f, startPos.y - 3.0f, startPos.z - 4.0f, 1.0f));
			sp->AddPoint(glm::vec4(endPos.x + 1.0f, endPos.y + 1.0f, endPos.z + 2.0f, 1.0f));
			sp->AddPoint(glm::vec4(endPos, 1.0f));
			sp->SetSpeed(5.0f);
			sp->SetClosedLoop(true);
			(*it)->SetSplineSource(sp);
		}
	}
}

void Missile::Draw()
{
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		(*it)->Draw();
	}
}

void Missile::AddMissile(vec3 p)
{
	st += 1;
	int end = 6;
	if (st < end && !(p.x == 100))
	{
		std::cout << glm::to_string(p) << std::endl;
		Add(p);
		//this->GetPosition();
		Trajectory();
	}
}

bool Missile::ParseLine(const std::vector<ci_string> &token)
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
