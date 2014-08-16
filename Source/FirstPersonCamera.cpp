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
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Update(float dt)
{
	EventManager::DisableMouseCursor();

	float pi = radians(180.0f);
	//Get postion and turned angle from the attached object(tank)
	glm::vec3 targetPosition = mTarget -> GetPosition();
	float tankHorizontalAngle = mTarget -> GetRotationAngle();
	float tankHAngleRadians = radians(tankHorizontalAngle);

	//Get turned angle from the canon
	float canonHorizontalAngle = mTarget -> GetChildHorizontalAngle();
	float canonVerticalAngle = mTarget -> GetChildVerticalAngle();
	float canonHAngleRadian = radians(canonHorizontalAngle);
	float canonVAngleRadian = radians(-canonVerticalAngle);

	//update postion and lookat for the camera
	mPosition = targetPosition + vec3(sinf(tankHAngleRadians + canonHAngleRadian) * cosf(atan2(mOffset.y, mOffset.z) + canonVAngleRadian) * (sqrtf(powf(mOffset.y, 2) + powf(mOffset.z, 2))), sinf(atan2(mOffset.y, mOffset.z) + canonVAngleRadian) * (sqrtf(powf(mOffset.y, 2) + powf(mOffset.z, 2))), cosf(tankHAngleRadians + canonHAngleRadian) * cosf(atan2(mOffset.y, mOffset.z) + canonVAngleRadian) * (sqrtf(powf(mOffset.y, 2) + powf(mOffset.z, 2))));
	mLookAtPoint = mPosition + vec3(sinf(tankHAngleRadians + canonHAngleRadian) * cosf(canonVAngleRadian), sinf(canonVAngleRadian), cosf(tankHAngleRadians + canonHAngleRadian)*cosf(canonVAngleRadian)); 
}

glm::mat4 FirstPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(		mPosition,		// Camera position
							mLookAtPoint,	// Look towards this point
							mUpVector		// Up vector
						);
}

void FirstPersonCamera::setTarget(Model* target){
	mTarget = target;
}