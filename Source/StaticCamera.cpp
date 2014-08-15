//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "StaticCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#include "EventManager.h"

using namespace glm;


StaticCamera::StaticCamera(glm::vec3 position, glm::vec3 lookAtPoint, glm::vec3 upVector) 
	: Camera(), mPosition(position), mLookAtPoint(lookAtPoint), mUpVector(upVector)
{
}

StaticCamera::~StaticCamera()
{
}

void StaticCamera::Update(float dt)
{
	EventManager::EnableMouseCursor();
}

glm::mat4 StaticCamera::GetViewMatrix() const
{
	return glm::lookAt(		mPosition,		// Camera position
							mLookAtPoint,	// Look towards this point
							mUpVector		// Up vector
						);
}
