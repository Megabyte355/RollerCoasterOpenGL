//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "FirstPersonCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#include "EventManager.h"

using namespace glm;


FirstPersonCamera::FirstPersonCamera(glm::vec3 offset, glm::vec3 lookAtPoint, glm::vec3 upVector) 
	: Camera()
{
	mOffset = offset;
	mLookAtPoint = lookAtPoint;
	mUpVector = upVector;
	mPosition = offset;
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Update(float dt)
{
	EventManager::DisableMouseCursor();

	//Get postion and turned angle from the attached object(tank)
	glm::vec3 parentPosition = mParent -> GetPosition();
	float tankHorizontalAngle = mParent -> GetRotationAngle();
	float tankHAngleRadians = radians(tankHorizontalAngle);

	//Get turned angle from the canon
	float canonHorizontalAngle = mParent -> GetChildHorizontalAngle();
	float canonVerticalAngle = mParent -> GetChildVerticalAngle();
	float canonHAngleRadian = radians(canonHorizontalAngle);
	float canonVAngleRadian = radians(-canonVerticalAngle);
	std::cout<<length(mOffset)<<":"<<canonVerticalAngle<<":"<<canonHorizontalAngle<<std::endl;

	//update postion and lookat for the camera
	//mPosition = parentPosition + mOffset;//vec3(mOffset.x - sinf(tankHAngleRadians) * mOffset.z, mOffset.y, cosf(tankHAngleRadians) * mOffset.z);
	//mLookAtPoint = parentPosition; //+ glm::vec3(length(mOffset)*cos(canonVAngleRadian) * sin(canonHAngleRadian), length(mOffset)*sin(canonVAngleRadian), length(mOffset)*cos(canonVAngleRadian) * cos(canonHAngleRadian));
	//vec3 mRight = glm::vec3(sin(canonHAngleRadian - radians(180.0f)/2.0f), 0, cos(canonHAngleRadian - radians(180.0f)/2.0f));
	//mUpVector = glm::cross(mRight, mLookAtPoint);
}

glm::mat4 FirstPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(		mPosition,		// Camera position
							mLookAtPoint,	// Look towards this point
							mUpVector		// Up vector
						);
}

void FirstPersonCamera::setParent(Model* parent){
	mParent = parent;
}