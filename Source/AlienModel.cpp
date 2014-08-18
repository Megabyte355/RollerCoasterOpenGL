//
// Contribution by Alin
//


#include "AlienModel.h"
#include "CubeModel.h"

using namespace std;

#include"sceneLoader.h"

sceneLoader* scene;

AlienModel::AlienModel()
{
	string filePath = "../Source/Models/alien/Drone.obj";
	scene = new sceneLoader(&filePath[0]);
}

AlienModel::~AlienModel()
{
	rotatingXAxis.clear();
	rotatingYAxis.clear();
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		delete *it;
	}
	container.clear();
}

void AlienModel::Update(float dt)
{	
	// @TODO 6 (Optional) - Here is where you can add some code if you want your vehicle to animate
}

void AlienModel::Draw()
{
	scene->draw(Renderer::GetShaderProgramID());
}

bool AlienModel::ParseLine(const std::vector<ci_string> &token)
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

void AlienModel::SetLightSource(LightModel * lightSource)
{
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		(*it)->SetLightSource(lightSource);
	}
}