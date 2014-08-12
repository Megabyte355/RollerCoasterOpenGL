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

	// Alternative 1, with mTurret as the cube parent works incorectly during control, cannot be implemented to mFrame parenting
	// due to incorect rescalling proportions.

	//// @TODO 5 - Layout your vehicle in a hierarchy
	//CubeModel * mTurret = new CubeModel(this);
	//CubeModel * mFrame = new CubeModel(mTurret);
	//CubeModel * mCanon = new CubeModel(mTurret);

	//// Tank Frame
	//container.push_back(mTurret);

	//// Tank Turret
 //   mFrame->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
 //   mFrame->SetScaling(glm::vec3(2.5f, 1.0f, 3.75f));
 //   container.push_back(mFrame);

	//// Tank Canon
 //   mCanon->SetPosition(glm::vec3(0.0f, 1.0f, 0.5f));
 //   mCanon->SetScaling(glm::vec3(0.15f, 0.35f, 0.8f));
 //   container.push_back(mCanon);

	// Alternative 2, parenting where there is a uniform hidden cube parent
	// @TODO 5 - Layout your vehicle in a hierarchy
	CubeModel * mCube = new CubeModel(this);
	CubeModel * mFrame = new CubeModel(mCube);
	CubeModel * mTurret = new CubeModel(mCube);
	CubeModel * mCanon = new CubeModel(mTurret);

	// Hidden cube parrent
	container.push_back(mCube);

	// Tank Frame
    mFrame->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    mFrame->SetScaling(glm::vec3(2.7f, 1.0f, 4.5f));
    container.push_back(mFrame);

	// Tank Turret
    mTurret->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    mTurret->SetScaling(glm::vec3(1.25f, 1.25f, 1.25f));
    container.push_back(mTurret);

	// Tank Canon
    mCanon->SetPosition(glm::vec3(0.0f, 0.0f, 1.25f));
    mCanon->SetScaling(glm::vec3(0.35f, 0.35f, 3.00f));
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
