//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "ThirdPersonCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#include "EventManager.h"

using namespace glm;


ThirdPersonCamera::ThirdPersonCamera(glm::vec3 offset, glm::vec3 lookAtPoint, glm::vec3 upVector) 
	: Camera()
{
	mOffset = offset;
	mLookAtPoint = lookAtPoint;
	mUpVector = upVector;
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::Update(float dt)
{
	EventManager::DisableMouseCursor();

	//Get postion and turned angle from the attached object(tank)
	glm::vec3 targetPosition = mTarget -> GetPosition();
	float tankHorizontalAngle = mTarget -> GetRotationAngle();
	float tankHAngleRadians = radians(tankHorizontalAngle);

	float canonHorizontalAngle = mTarget -> GetChildHorizontalAngle();
	float canonVerticalAngle = mTarget -> GetChildVerticalAngle();
	float canonHAngleRadian = radians(canonHorizontalAngle);
	float canonVAngleRadian = radians(-canonVerticalAngle);

	//update postion and lookat for the camera
	mPosition = targetPosition + vec3(mOffset.x + sinf(tankHAngleRadians + canonHAngleRadian) * mOffset.z, mOffset.y - 5 * sinf(canonVAngleRadian), cosf(tankHAngleRadians + canonHAngleRadian) * mOffset.z);
	mLookAtPoint = targetPosition + vec3(0.0f, 5 * sinf(canonVAngleRadian), 0.0f); 
	
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(		mPosition,		// Camera position
							mLookAtPoint,	// Look towards this point
							mUpVector		// Up vector
						);
}

void ThirdPersonCamera::setTarget(Model* target){
	mTarget = target;
}