// Contributors:
//      Gary Chang

#include "CubeSMController.h"
#include "CubeMovingState.h"

CubeSMController::CubeSMController(CubeModelSM* model) : SMController(model)
{
    cubeModel = model;
    Init();
}

CubeSMController::~CubeSMController()
{
    cubeModel = nullptr;
    for (std::vector<State*>::iterator it = states.begin(); it < states.end(); ++it)
    {
        delete *it;
    }
    states.clear();
}

void CubeSMController::Update(float dt)
{
    currentState->Execute(dt);
}

void CubeSMController::Init()
{
    // Define all Cube states here
    CubeMovingState* movingState = new CubeMovingState(cubeModel);

    states.push_back(movingState);
    currentState = movingState;
}