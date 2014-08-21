// Contributors:
//      Dong Li

//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Camera.h"

class FreeLookCamera : public Camera
{
public:
	FreeLookCamera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up);
	virtual ~FreeLookCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;

	virtual void setTarget(Model* parent);

private:
	// @TODO 3 - Add every parameter you need for a first person camera
	//           including the speed of the camera

    glm::vec3 mPosition;
    glm::vec3 mLookAt;
    glm::vec3 mRight;
    glm::vec3 mUp;

    float hAngle;
    float vAngle;

    float moveSpeed;
    float mouseSpeed;

    bool spaceReleased = true;
};
