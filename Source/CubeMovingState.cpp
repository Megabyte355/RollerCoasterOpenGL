// Contributors:
//      Gary Chang

#include "CubeMovingState.h"
#include "BSpline.h"

#include <iostream>

CubeMovingState::CubeMovingState(CubeModelSM* model)
{
    cubeModel = model;
    name = "CubeMovingState";
}

CubeMovingState::~CubeMovingState()
{
    cubeModel = nullptr;
}

void CubeMovingState::In()
{
    duration = 3.0f;
}

void CubeMovingState::Out()
{
    nextStateName = "CubeIdleState";
}

void CubeMovingState::Execute(float dt)
{
    BSpline* spline = cubeModel->GetSpline();
    if (spline != nullptr)
    {
        cubeModel->SetPosition(spline->GetPosition() + spline->GetNextPoint());
        if (cubeModel->LooksForward())
        {
            glm::vec3 velocity = glm::vec3(spline->GetVelocityUnitVector());
            glm::vec3 forwardVector = cubeModel->mForward;
            glm::vec3 rotationAxis = glm::cross(forwardVector, velocity);
            float rotationAngleInDegrees = degrees(glm::acos(glm::dot(forwardVector, velocity) / (length(forwardVector) * length(velocity))));
            
            cubeModel->SetRotation(rotationAxis, rotationAngleInDegrees);
        }
        spline->Update(dt);
    }

    duration -= dt;
}

void CubeMovingState::Init()
{

}

bool CubeMovingState::IsExpired()
{
    return duration <= 0.0f;
}