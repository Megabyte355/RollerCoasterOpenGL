#include "Missile.h"
#include "CubeModel.h"
#include "TankModel.h"
#include "BSpline.h"
#include "World.h"

using namespace glm;
using namespace std;
#include "glm/ext.hpp"

int st;
bool flag;
std::vector<CubeModel*> container;
TankModel* tk;
BSpline* sp;

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
	glm::vec3 pos = glm::vec3(tk->GetPosition());
	std::cout << glm::to_string(pos) << std::endl;
}

void Missile::Trajectory()
{
	/*sp = new BSpline();
	sp->AddPoint(glm::vec4(this->GetPosition(),1.0f));
	sp->AddPoint(glm::vec4(2.0f, 0.0f, 1.0f, 1.0f));
	sp->AddPoint(glm::vec4(4.0f, 1.0f, 2.0f, 1.0f));
	sp->AddPoint(glm::vec4(glm::vec3(tk->GetPosition()),1.0f));
	sp->Update(20);*/
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
		flag = true;
		std::cout << glm::to_string(p) << std::endl;
		Add(p);
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
