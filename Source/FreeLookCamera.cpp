//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "FreeLookCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>
#include "RayCast.h"
#include "World.h"

using namespace glm;

FreeLookCamera::FreeLookCamera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up) : Camera()
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

FreeLookCamera::~FreeLookCamera()
{
}

void FreeLookCamera::Update(float dt)
{
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();

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
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        //vec4 originPoint, vec4 directionVector, vec4 p1, vec4 p2, vec4 p3
        std::vector<Model::Vertex> tempVec = (*World::GetModelsPtr())[2]->GetWorldVertices();
        vec3 p1 = tempVec[0].position;
        vec3 p2 = tempVec[1].position;
        vec3 p3 = tempVec[2].position;

        int testResult = RayCast::IsPlaneIntersecting(vec4(mPosition, 1.0f), vec4(mLookAt, 1.0f), p1, p2, p3);
        //int distanceResult = RayCast::LinePlaneIntersection(vec4(mPosition, 1.0f), vec4(mLookAt, 1.0f), p1, p2, p3);
    }
}

glm::mat4 FreeLookCamera::GetViewMatrix() const
{
	// @TODO 3 : Calculate the View Matrix
    return glm::lookAt(mPosition, mPosition + mLookAt, mUp);
}

void FreeLookCamera::setTarget(Model* parent)
{

}