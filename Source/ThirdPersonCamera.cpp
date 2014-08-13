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
	glm::vec3 parentPosition = mParent -> GetPosition();
	float tankHorizontalAngle = mParent -> GetRotationAngle();
	float tankHAngleRadians = radians(tankHorizontalAngle);

	//update postion and lookat for the camera
	mPosition = parentPosition + vec3(mOffset.x + sinf(tankHAngleRadians) * mOffset.z, mOffset.y, cosf(tankHAngleRadians) * mOffset.z);
	mLookAtPoint = parentPosition; 
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(		mPosition,		// Camera position
							mLookAtPoint,	// Look towards this point
							mUpVector		// Up vector
						);
}

void ThirdPersonCamera::setParent(Model* parent){
	mParent = parent;
}