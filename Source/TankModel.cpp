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
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>


using namespace glm;

TankModel::TankModel()
{
	//tank bottom
	CubeModel * mBase = new CubeModel(this,vec3(2.0f, 1.0f, 4.0f));
	container.push_back(mBase);

	// Tank Top
	CubeModel * mTop = new CubeModel(mBase, vec3(1.0f, 1.5f, 1.0f));
	mTop->SetPosition(vec3(0.0f, 0.75f, 0.0f));
    container.push_back(mTop);

	// Tank Canon
	CubeModel * mCanon = new CubeModel(mTop, vec3(0.3f, 0.3f, 2.0f));
	mCanon->SetPosition(glm::vec3(0.0f, 0.25f, 1.5f));
	container.push_back(mCanon);

	canonHorizontalAngle = 0.0f;
	canonVerticalAngle = 0.0f;
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
	glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

    // Update body position
    vec3 delta = vec3(0.0f, 0.0f, 0.0f);
	float moveSpeed = 4.0f;
	float bodyAngularSpeed = 90.0f;

	if (mRotationAngleInDegrees > 360)
	{
		mRotationAngleInDegrees -= 360;
	}
	else if (mRotationAngleInDegrees < -360)
	{
		mRotationAngleInDegrees += 360;
	}
	float rotationAngleInRadian = radians(mRotationAngleInDegrees);

    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        delta = delta + zAxis * (dt * moveSpeed * cos(rotationAngleInRadian)) 
					+ xAxis * (dt * moveSpeed * sin(rotationAngleInRadian));
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        delta = delta - zAxis * (dt * moveSpeed * cos(rotationAngleInRadian)) 
					- xAxis * (dt * moveSpeed * sin(rotationAngleInRadian));
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
		mRotationAxis = yAxis;
		mRotationAngleInDegrees += bodyAngularSpeed * dt;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mRotationAxis = yAxis;
		mRotationAngleInDegrees -= bodyAngularSpeed * dt;
    }
    mPosition += delta;
	
	//update cannon position
	float cannonAngularSpeed = 2.5f;
	
	//float canonRotationAngle = container.at(1)->GetRotationAngle();
    
	canonHorizontalAngle -= EventManager::GetMouseMotionX() * cannonAngularSpeed * dt;
	canonVerticalAngle   += EventManager::GetMouseMotionY() * cannonAngularSpeed * dt;

	canonVerticalAngle = std::max(-55.0f, std::min(10.0f, canonVerticalAngle));
	canonHorizontalAngle = std::max(-75.0f, std::min(75.0f, canonHorizontalAngle));
	
	container.at(1) -> SetRotation(xAxis, canonVerticalAngle);
	//vec3 a = container.at(1)->GetRotationAxis();
	//std::cout<<a.x<<","<<a.y<<","<<a.z<<":"<<canonVerticalAngle<<":"<<canonHorizontalAngle<<std::endl;

	//container.at(1) -> SetSecondRotation(yAxis,canonHorizontalAngle);
	
	//vec3 b = container.at(1)->GetRotationAxis();
	//std::cout<<b.x<<","<<b.y<<","<<b.z<<":"<<canonVerticalAngle<<":"<<canonHorizontalAngle<<std::endl;
	//float canonHorizontalRadians = radians(canonHorizontalAngle);
	//float canonVerticalRadians = radians(canonVerticalAngle);
	/*
	mat4 identityMatrix(1.0f);
	mat4 xRotationMatrix = glm::rotate(identityMatrix, canonVerticalAngle, xAxis);
	mat4 yRotationMatrix = glm::rotate(identityMatrix, canonHorizontalAngle, yAxis);
	mat4 totalRotationMartix = xRotationMatrix * yRotationMatrix;
	float totalRotationAngle = acos(( totalRotationMartix[0][0] + totalRotationMartix[1][1] + totalRotationMartix[2][2] - 1)/2);
	float x = (totalRotationMartix[2][1] - totalRotationMartix[1][2])/sqrtf(powf((totalRotationMartix[2][1] - totalRotationMartix[1][2]), 2) + powf((totalRotationMartix[0][2] - totalRotationMartix[2][0]), 2) + powf((totalRotationMartix[1][0] - totalRotationMartix[0][1]), 2));
    float y = (totalRotationMartix[0][2] - totalRotationMartix[2][0])/sqrtf(powf((totalRotationMartix[2][1] - totalRotationMartix[1][2]), 2) + powf((totalRotationMartix[0][2] - totalRotationMartix[2][0]), 2) + powf((totalRotationMartix[1][0] - totalRotationMartix[0][1]), 2));
	float z = (totalRotationMartix[1][0] - totalRotationMartix[0][1])/sqrtf(powf((totalRotationMartix[2][1] - totalRotationMartix[1][2]), 2) + powf((totalRotationMartix[0][2] - totalRotationMartix[2][0]), 2) + powf((totalRotationMartix[1][0] - totalRotationMartix[0][1]), 2));
	vec3 totalRotationAxis = vec3(x, y, z);

	container.at(1) -> SetRotation(totalRotationAxis, totalRotationAngle);
	*/
	// @TODO 6 (Optional) - Here is where you can add some code if you want your vehicle to animate
	/*glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f); yRotationMatrix
    
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
