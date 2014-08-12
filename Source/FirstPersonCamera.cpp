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


FirstPersonCamera::FirstPersonCamera(glm::vec3 position, glm::vec3 lookAtPoint, glm::vec3 upVector) 
	: Camera()
{
	mPosition = position;
	mLookAtPoint = lookAtPoint;
	mUpVector = upVector;
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Update(float dt)
{
	//EventManager::EnableMouseCursor();
	EventManager::DisableMouseCursor();

	glm::vec3 parentPosition = mParent -> GetPosition();
	mPosition = parentPosition - vec3(0.0f, -1.5f, 0.0f) + vec3(0.0f, 1.5f, -5.0f);
	mLookAtPoint = parentPosition - vec3(0.0f, -1.5f, 0.0f);

	float mHorizontalAngle = mParent -> GetRotationAngle();
	float theta = radians(mHorizontalAngle);
	glm::vec3 mLookAt = vec3(cosf(theta), 0, -sinf(theta));

	mLookAtPoint = mLookAtPoint + vec3(sinf(theta) , 0, -cosf(theta));


	//std::cout<<"position"<<mPosition.x<<mPosition.y<<mPosition.z<<std::endl;
	//std::cout<<mLookAtPoint.x<<mLookAtPoint.y<<mLookAtPoint.z<<std::endl;
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