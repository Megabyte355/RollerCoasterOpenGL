//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "TankModel.h"
#include "Renderer.h"
#include "EventManager.h"
#include "CubeModel.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace glm;

TankModel::TankModel()
{
	// @TODO 5 - Layout your vehicle in a hierarchy
	CubeModel * mBase = new CubeModel(this);
	CubeModel * mFrame = new CubeModel(mBase);
	CubeModel * mCanon = new CubeModel(mFrame);

	// Body
	container.push_back(mBase);

	// Tank Base
    mFrame->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    mFrame->SetScaling(glm::vec3(2.5f, 1.0f, 3.75f));
    container.push_back(mFrame);

	// Tank Canon
    mCanon->SetPosition(glm::vec3(0.0f, 1.0f, 0.5f));
    mCanon->SetScaling(glm::vec3(0.15f, 0.25f, 0.8f));
    container.push_back(mCanon);
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
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	// mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

	float moveSpeed = 4.0f;
	float pi = 3.1415926f;
    glm::vec3 xDirection(1.0f, 0.0f, 0.0f);
    glm::vec3 zDirection(0.0, 0.0f, 1.0f);

    // Update camera position
    vec3 delta = vec3(0.0f, 0.0f, 0.0f);
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        delta = delta + zDirection * (dt * moveSpeed * cos(mRotationAngleInDegrees*pi/180.0f)) 
					+ xDirection * (dt * moveSpeed * sin(mRotationAngleInDegrees*pi/180.0f));
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        delta = delta - zDirection * (dt * moveSpeed * cos(mRotationAngleInDegrees*pi/180.0f)) 
					- xDirection * (dt * moveSpeed * sin(mRotationAngleInDegrees*pi/180.0f));
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
		mRotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		mRotationAngleInDegrees += 90 * dt;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mRotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		mRotationAngleInDegrees -= 90 * dt;
    }

    mPosition += delta;
	// @TODO 6 (Optional) - Here is where you can add some code if you want your vehicle to animate
	/*glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    
	mCanonBullet->SetRotation(zAxis, mCanonBullet->GetRotationAngle() + 360 * dt);*/

}

void TankModel::Draw()
{
	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// @TODO 5 - Draw Each part of your vehicle here
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
