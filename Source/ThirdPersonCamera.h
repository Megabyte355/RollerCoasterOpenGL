//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Camera.h"
#include "Model.h"

class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera(glm::vec3 offset, glm::vec3 lookAtPoint, glm::vec3 upVector);
	virtual ~ThirdPersonCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;

	virtual void setParent(Model* parent);

private:
	glm::vec3 mPosition;
	glm::vec3 mOffset;
	glm::vec3 mLookAtPoint;
	glm::vec3 mUpVector;

	Model* mParent;
};
