//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "FirstPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>

using namespace glm;

FirstPersonCamera::FirstPersonCamera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up) : Camera()
{
    mPosition = position;
    mLookAt = lookAt;
    mUp = up;
    mRight = glm::cross(mLookAt, mUp);

    hAngle = radians(180.0f);
    vAngle = 0.0f;
    moveSpeed = 4.0f;
    mouseSpeed = 0.10f;
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Update(float dt)
{
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();

	// @TODO 3 : You need to move the Camera based on the User inputs
	// - You can access the mouse motion with EventManager::GetMouseMotionXY()
	// - For mapping A S D W, you can look in World.cpp for an example of accessing key states
	// - Don't forget to use dt to control the speed of the camera motion

	// Update orientation
    hAngle += mouseSpeed * dt * - EventManager::GetMouseMotionX();
    vAngle += mouseSpeed * dt * - EventManager::GetMouseMotionY();

    // Clamping and Wrap-around angles
    vAngle = glm::clamp(vAngle, glm::radians(-85.0f), glm::radians(85.0f));
    if (degrees(hAngle) > 180.0f)
    {
        hAngle -= radians(360.0f);
    }
    else if (degrees(hAngle) < -180.0f)
    {
        hAngle += radians(360.0f);
    }

    // Update direction vectors
    mLookAt = glm::vec3(cos(vAngle) * sin(hAngle), sin(vAngle), cos(vAngle) * cos(hAngle));
    mRight = glm::vec3(sin(hAngle - radians(180.0f)/2.0f), 0, cos(hAngle - radians(180.0f)/2.0f));
    mUp = glm::cross(mRight, mLookAt);

    // Update camera position
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        mPosition += mLookAt * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        mPosition -= mLookAt * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        mPosition += mRight * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        mPosition -= mRight * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
    {
        mPosition -= mUp * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
    {
        mPosition += mUp * dt * moveSpeed;
    }
}

glm::mat4 FirstPersonCamera::GetViewMatrix() const
{
	// @TODO 3 : Calculate the View Matrix
    return glm::lookAt(mPosition, mPosition + mLookAt, mUp);
}