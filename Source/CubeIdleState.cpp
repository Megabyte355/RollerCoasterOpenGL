// Contributors:
//      Gary Chang

#include "CubeIdleState.h"
#include "BSpline.h"

#include <iostream>

CubeIdleState::CubeIdleState(CubeModelSM* model)
{
    cubeModel = model;
    name = "CubeIdleState";
}

CubeIdleState::~CubeIdleState()
{
    cubeModel = nullptr;
}

void CubeIdleState::In()
{
    duration = 5.0f;
}

void CubeIdleState::Out()
{

}

void CubeIdleState::Execute(float dt)
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
}

void CubeIdleState::Init()
{

}

bool CubeIdleState::IsExpired()
{
    // Temporary
    return false;
}