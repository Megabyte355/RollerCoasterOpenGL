#include "Missile.h"
#include "CubeModel.h"
#include "TankModel.h"
#include "BSpline.h"
#include "World.h"

using namespace glm;
using namespace std;
//#include "glm/ext.hpp"

int st;
bool flag;
std::vector<CubeModel*> container;
TankModel* tk;
BSpline* sp;

Missile::Missile(TankModel* t)
{
	tk = t;
	sp = nullptr;
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
	flag = false;
	
}

void Missile::Add(vec3 position)
{
	CubeModel* dada = new CubeModel();
	dada->SetPosition(position);
	container.push_back(dada);
}

void Missile::Update(float dt)
{
	if (sp != nullptr)
	{
		this->mPosition = sp->GetPosition() + sp->GetNextPoint();
		sp->Update(dt);
	}
}

void Missile::Trajectory()
{
	sp->AddPoint(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	sp->AddPoint(glm::vec4(2.0f, 0.0f, 1.0f, 1.0f));
	sp->AddPoint(glm::vec4(3.0f, 1.0f, 2.0f, 1.0f));
	sp->AddPoint(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	sp->SetSpeed(1.0f);
	sp->SetClosedLoop(false);
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
	int end = 1;
	//hack location
	if (p.x == 100)
	{
		st = 0;
	}
	// true location
	if (st == end && !(flag))
	{
		sp = new BSpline();
		flag = true;
		//std::cout << glm::to_string(p) << std::endl;
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
