//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "TankModel.h"
#include "CubeModel.h"


using namespace std;
using namespace glm;

TankModel::TankModel()
{
	// @TODO 5 - Layout your vehicle in a hierarchy
	CubeModel * mBase = new CubeModel(this);
	CubeModel * mFrame = new CubeModel(mBase);
	CubeModel * mCanon = new CubeModel(mBase);

	// Body
	container.push_back(mBase);

	// Tank Base
    mFrame->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    mFrame->SetScaling(glm::vec3(2.5f, 1.0f, 3.75f));
    container.push_back(mFrame);

	// Tank Canon
    mCanon->SetPosition(glm::vec3(0.0f, 0.0f, 1.5f));
    mCanon->SetScaling(glm::vec3(0.25f, 0.25f, 3.0f));
    container.push_back(mCanon);
}

TankModel::~TankModel()
{
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		delete *it;
	}
	container.clear();
}

void TankModel::Update(float dt)
{	
	// @TODO 6 (Optional) - Here is where you can add some code if you want your vehicle to animate
	/*glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    
	mCanonBullet->SetRotation(zAxis, mCanonBullet->GetRotationAngle() + 360 * dt);*/
}

void TankModel::Draw()
{
	// @TODO 5 - Draw Each part of your vehicle here
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		(*it)->Draw();
	}
}

bool TankModel::ParseLine(const std::vector<ci_string> &token)
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

void TankModel::SetLightSource(LightModel * lightSource)
{
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		(*it)->SetLightSource(lightSource);
	}
}
