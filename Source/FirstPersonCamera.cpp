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

	//Get postion and turned angle from the attached object
	glm::vec3 parentPosition = mParent -> GetPosition();
	float mHorizontalAngle = mParent -> GetRotationAngle();
	float mHorizontalRadians = radians(mHorizontalAngle);

	//update postion and lookat for the camera
	mPosition = parentPosition + vec3(mOffset.x + sinf(mHorizontalRadians) * mOffset.z, mOffset.y, cosf(mHorizontalRadians) * mOffset.z);
	mLookAtPoint = parentPosition;

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