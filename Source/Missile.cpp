// Contributors:
//      Razvan Alin Cijov

#include "Missile.h"
#include "CubeModel.h"
#include "TankModel.h"
#include "BSpline.h"
#include "World.h"

using namespace glm;
using namespace std;
#include "glm/ext.hpp"

int st;
std::vector<Missile*> mContainer;
std::vector<CubeModel*> container;
TankModel* tk;

Missile::Missile(void)
{
}

Missile::Missile(TankModel* t)
{
	tk = t;
	Init();
}


Missile::~Missile(void)
{
	container.clear();
	mContainer.clear();
	for (vector<Missile*>::iterator it = mContainer.begin(); it < mContainer.end(); ++it)
	{
		delete *it;
	}
}

void Missile::Init()
{
	st = 0;	
}

void Missile::Add(vec3 position)
{
	cube = new CubeModel(this);
	cube->SetPosition(position);
	container.push_back(cube);

}

void Missile::Update(float dt)
{

		for (vector<Missile*>::iterator it = mContainer.begin(); it < mContainer.end(); ++it)
		{
			cube = (*it)->GetCube();
			cube->SetPosition(cube->GetBSpline()->GetPosition() + cube->GetBSpline()->GetNextPoint());
			cube->GetBSpline()->Update(dt);
			if (cube->GetBSpline()->LastPointReached())
			{
				// delete cube;
				cube->SetPosition(glm::vec3(0.0f, -3.0f, 0.0f));
			}
		}

}

void Missile::Trajectory(BSpline* sp)
{
		glm::vec3 startPos = cube->GetPosition();
		glm::vec3 endPos = tk->GetPosition();

		sp->AddPoint(glm::vec4(startPos, 1.0f));
		sp->AddPoint(glm::vec4(startPos.x - 1.0f, startPos.y - 3.0f, startPos.z - 4.0f, 1.0f));
		sp->AddPoint(glm::vec4(endPos.x + 1.0f, endPos.y + 1.0f, endPos.z + 2.0f, 1.0f));
		sp->AddPoint(glm::vec4(endPos, 1.0f));
		sp->SetSpeed(5.0f);
		sp->SetClosedLoop(false);
		cube->SetSplineSource(sp);
}

void Missile::Draw()
{
	for (vector<Missile*>::iterator it = mContainer.begin(); it < mContainer.end(); ++it)
	{
		cube = (*it)->GetCube();
		cube->Draw();
	}
}

void Missile::AddMissile(vec3 p)
{
	if (!(p.x == 100))
	{
		Missile* ms = new Missile(tk);
		BSpline* bs = new BSpline();
		ms->Add(p);
		ms->Trajectory(bs);
		mContainer.push_back(ms);
		//std::cout << glm::to_string(p) << std::endl;
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