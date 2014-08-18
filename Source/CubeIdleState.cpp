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
    duration = 1.0f;
}

void CubeIdleState::Out()
{
    nextStateName = "CubeMovingState";
}

void CubeIdleState::Execute(float dt)
{
    duration -= dt;
}

void CubeIdleState::Init()
{

}

bool CubeIdleState::IsExpired()
{
    return duration <= 0.0f;
}