// Contributors:
//      Gary Chang

#include "CubeMovingState.h"
#include "BSpline.h"

#include <iostream>

CubeMovingState::CubeMovingState(CubeModelSM* model)
{
    cubeModel = model;
}

CubeMovingState::~CubeMovingState()
{
    cubeModel = nullptr;
}

void CubeMovingState::In()
{

}

void CubeMovingState::Out()
{

}

void CubeMovingState::Execute(float dt)
{
    BSpline* spline = cubeModel->GetSpline();
    if (spline != nullptr)
    {
        cubeModel->SetPosition(spline->GetPosition() + spline->GetNextPoint());
        spline->Update(dt);
    }

    //std::cout << "Position.x - " << cubeModel->GetPosition().x << std::endl;
    //std::cout << "Position.y - " << cubeModel->GetPosition().y << std::endl;
    //std::cout << "Position.z - " << cubeModel->GetPosition().z << std::endl << std::endl << std::endl;

    //if (spline != nullptr)
    //{
    //    this->mPosition = spline->GetPosition() + spline->GetNextPoint();

    //    if (lookForward)
    //    {
    //        glm::vec3 velocity = glm::vec3(spline->GetVelocityUnitVector());
    //        mRotationAxis = glm::cross(mForward, velocity);
    //        mRotationAngleInDegrees = degrees(glm::acos(glm::dot(mForward, velocity) / (length(mForward) * length(velocity))));
    //    }
    //    spline->Update(dt);
    //}
}

void CubeMovingState::Init()
{

}