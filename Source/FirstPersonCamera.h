// Contributors:
//      Razvan Alin Cijov
//      Gary Chang
//      Dong Li
//      Oleksandr Dymov

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

class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera(glm::vec3 offset, glm::vec3 lookAtPoint, glm::vec3 upVector);
	virtual ~FirstPersonCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;

	virtual void setTarget(Model* target);

	virtual void SetCameraShake(float amplitude, float adjustAmplitudePerSecond);
	virtual void StartCameraShake(float dt);

private:
	glm::vec3 mPosition;
	glm::vec3 mOffset;
	glm::vec3 mLookAtPoint;
	glm::vec3 mUpVector;

	float amplitude;
	float adjustAmplitudePerSecond;
	float timeElapsed;

	Model* mTarget;

    bool buttonReleased = true;
    bool spaceReleased = true;
};
