// Contributors:
//      Gary Chang

#include "CubeSMController.h"
#include "CubeMovingState.h"

CubeSMController::CubeSMController(CubeModelSM* model) : SMController(model)
{
    cubeModel = model;
}

CubeSMController::~CubeSMController()
{
    cubeModel = nullptr;
}

void CubeSMController::Update(float dt)
{

}

void CubeSMController::Init()
{
    // Define all Cube states here
    CubeMovingState* movingState = new CubeMovingState(cubeModel);

    states.push_back(movingState);
    currentState = movingState;
}