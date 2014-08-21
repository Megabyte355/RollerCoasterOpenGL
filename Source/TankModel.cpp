// Contributors:
//      Dong Li
//      Oleksandr Dymov

//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "World.h"
#include "StaticCamera.h"
#include "FirstPersonCamera.h"
#include "FreeLookCamera.h"
#include "TankModel.h"
#include "Renderer.h"
#include "EventManager.h"
#include "CubeModel.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>


using namespace std;
using namespace glm;

TankModel::TankModel()
{

	// Alternative 2, parenting where there is a uniform hidden cube parent
	CubeModel * mCube = new CubeModel(this, vec3(0.5, 0.5, 0.5));
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

	mChildHorizontalAngle = 0.0f;
	mChildVerticalAngle = 0.0f;
}

TankModel::~TankModel()
{
	for (std::vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		delete *it;
	}
	container.clear();
}

void TankModel::Update(float dt)
{
	//Tank cannot be moved under free look camera
	if(World::GetCurrentCameraNumber() != 2)
	{
		glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

		// Update body(tank) position and rotation
		vec3 delta = vec3(0.0f, 0.0f, 0.0f);
		float moveSpeed = 4.0f;
		float bodyAngularSpeed = 20.0f;

		if (mRotationAngleInDegrees > 360)
		{
			mRotationAngleInDegrees -= 360;
		}
		else if (mRotationAngleInDegrees < -360)
		{
			mRotationAngleInDegrees += 360;
		}
		float rotationAngleInRadian = radians(mRotationAngleInDegrees);

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			delta = delta + zAxis * (dt * moveSpeed * cos(rotationAngleInRadian)) 
						+ xAxis * (dt * moveSpeed * sin(rotationAngleInRadian));
		}
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			delta = delta - zAxis * (dt * moveSpeed * cos(rotationAngleInRadian)) 
						- xAxis * (dt * moveSpeed * sin(rotationAngleInRadian));
		}
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			mRotationAxis = yAxis;
			mRotationAngleInDegrees += bodyAngularSpeed * dt;
		}
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			mRotationAxis = yAxis;
			mRotationAngleInDegrees -= bodyAngularSpeed * dt;
		}

		vec3 positionNoClamp = mPosition + delta;

		//Clamp tank position so it will not run out of the ground. 
		positionNoClamp = vec3(std::max(-46.5f, std::min(46.5f, positionNoClamp.x)), positionNoClamp.y, std::max(-46.5f, std::min(46.5f, positionNoClamp.z)));
		mPosition = positionNoClamp;
	
		//update Turret/cannon position and rotation
		float cannonAngularSpeed = 2.5f;

		mChildHorizontalAngle -= EventManager::GetMouseMotionX() * cannonAngularSpeed * dt;
		mChildVerticalAngle   += EventManager::GetMouseMotionY() * cannonAngularSpeed * dt;

		mChildVerticalAngle = std::max(-40.0f, std::min(7.0f, mChildVerticalAngle));
		//mChildHorizontalAngle = std::max(-70.0f, std::min(70.0f, mChildHorizontalAngle));
		if (mRotationAngleInDegrees > 360)
		{
			mRotationAngleInDegrees -= 360;
		}
		else if (mRotationAngleInDegrees < -360)
		{
			mRotationAngleInDegrees += 360;
		}
	
		//set y-axis rotation to turret
		container.at(2) -> SetRotation(yAxis,mChildHorizontalAngle);
		//set x-axis rotation to Turret
		container.at(2) -> SetSecondRotation(xAxis, mChildVerticalAngle);
	}	
}

void TankModel::Draw()
{
	for (std::vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
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
	for (std::vector<CubeModel*>::iterator it = container.begin(); it < container.end(); ++it)
	{
		(*it)->SetLightSource(lightSource);
	}
}

vec3 TankModel::GetCanonTipPoint()
{
	vec3 canonTipPosition;

	// get the radians of  the tank's rotation
	float rotationAngleInRadian = radians(mRotationAngleInDegrees);
	// get the radians of  the canon's rotation
	float mChildHorizontalRadian = radians(mChildHorizontalAngle);
	float mChildVerticalRadian = radians(-mChildVerticalAngle);

	//3.5 is the sum of the canon's length and half of the turret's length
	canonTipPosition = GetPosition() + vec3(3.5 * cosf(mChildVerticalRadian) * sinf(rotationAngleInRadian + mChildHorizontalRadian), 3.5 * sinf(mChildVerticalRadian), 3.5 * cosf(mChildVerticalRadian) * cosf(rotationAngleInRadian + mChildHorizontalRadian));

	return canonTipPosition;
}
vec3 TankModel::GetCanonDirectionVector()
{
	vec3 canonDirectoin;

	//normalized canon direction
	canonDirectoin = normalize(GetCanonTipPoint() - GetPosition());

	return canonDirectoin;

}
