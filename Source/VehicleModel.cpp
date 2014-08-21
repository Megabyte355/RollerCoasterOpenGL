// Contributors:
//      Gary Chang

//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "VehicleModel.h"
#include "CubeModel.h"

using namespace std;
using namespace glm;

VehicleModel::VehicleModel()
{
	angularSpeedXAxis = 900.0f;
	angularSpeedYAxis = 720.0f;
	
	// @TODO 5 - Layout your vehicle in a hierarchy
	CubeModel * mBody = new CubeModel(this);
	CubeModel * mFront = new CubeModel(mBody);
	CubeModel * mTail = new CubeModel(mBody);
	CubeModel * mTailWing = new CubeModel(mTail);
	CubeModel * mShaft = new CubeModel(mBody);
	CubeModel * mBlade1 = new CubeModel(mShaft);
	CubeModel * mBlade2 = new CubeModel(mShaft);
	CubeModel * mTailBlade1 = new CubeModel(mTailWing);
	CubeModel * mTailBlade2 = new CubeModel(mTailWing);

	// Body
	container.push_back(mBody);

    // Front
    mFront->SetPosition(glm::vec3(0.0f, -0.25f, 0.75f));
    mFront->SetScaling(glm::vec3(1.0f, 0.5f, 0.75f));
    container.push_back(mFront);

    // Tail
    mTail->SetPosition(glm::vec3(0.0f, -0.0f, -1.4f));
    mTail->SetScaling(glm::vec3(0.25f, 0.5f, 1.9f));
    container.push_back(mTail);

    // Tail Wing
    mTailWing->SetPosition(glm::vec3(0.0f, 0.25f, -0.7f));
    mTailWing->SetScaling(glm::vec3(1.0f, 1.5f, 0.4f));
    container.push_back(mTailWing);

    // Shaft
    mShaft->SetPosition(glm::vec3(0.0f, 0.55f, 0.0f));
    mShaft->SetScaling(glm::vec3(0.1f, 0.5f, 0.1f));
    container.push_back(mShaft);

    // Blade1
    mBlade1->SetPosition(glm::vec3(0.0f, 0.5f, 0.0f));
    mBlade1->SetScaling(glm::vec3(35.0f, 0.1f, 1.0f));
    container.push_back(mBlade1);
    rotatingYAxis.push_back(mBlade1);

    // Blade2
    mBlade2->SetPosition(glm::vec3(0.0f, 0.5f, 0.0f));
    mBlade2->SetScaling(glm::vec3(1.0f, 0.1f, 35.0f));
    container.push_back(mBlade2);
    rotatingYAxis.push_back(mBlade2);

    // TailBlade1
    mTailBlade1->SetPosition(glm::vec3(0.65f, 0.35f, -0.35f));
    mTailBlade1->SetScaling(glm::vec3(0.2f, 2.25f, 0.15f));
    container.push_back(mTailBlade1);
    rotatingXAxis.push_back(mTailBlade1);

    // TailBlade2
    mTailBlade2->SetPosition(glm::vec3(0.65f, 0.35f, -0.35f));
    mTailBlade2->SetScaling(glm::vec3(0.2f, 0.15f, 2.25f));
    container.push_back(mTailBlade2);
    rotatingXAxis.push_back(mTailBlade2);
}

VehicleModel::~VehicleModel()
{
	rotatingXAxis.clear();
	rotatingYAxis.clear();
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		delete *it;
	}
	container.clear();
}

void VehicleModel::Update(float dt)
{	
	// @TODO 6 (Optional) - Here is where you can add some code if you want your vehicle to animate
    glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);

	for (vector<CubeModel*>::iterator it = rotatingXAxis.begin(); it < rotatingXAxis.end(); ++it)
	{
		(*it)->SetRotation(xAxis, (*it)->GetRotationAngle() + angularSpeedXAxis * dt);
	}

	for (vector<CubeModel*>::iterator it = rotatingYAxis.begin(); it < rotatingYAxis.end(); ++it)
	{
		(*it)->SetRotation(yAxis, (*it)->GetRotationAngle() + angularSpeedYAxis * dt);
	}
}

void VehicleModel::Draw()
{
	// @TODO 5 - Draw Each part of your vehicle here
    for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		(*it)->Draw();
	}
}

bool VehicleModel::ParseLine(const std::vector<ci_string> &token)
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

void VehicleModel::SetLightSource(LightModel * lightSource)
{
	for (vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		(*it)->SetLightSource(lightSource);
	}
}