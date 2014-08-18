// Contributors:
//      Gary Chang

#include "CubeSMController.h"
#include "CubeMovingState.h"
#include "CubeIdleState.h"

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
    if (currentState->IsExpired())
    {
        currentState->Out();
        
        std::string nextStateName = currentState->GetNextStateName();
        for (std::vector<State*>::iterator it = states.begin(); it < states.end(); ++it)
        {
            if ((*it)->GetName() == nextStateName)
            {
                currentState = *it;
                break;
            }
        }
        currentState->In();
    }
}

void CubeSMController::Init()
{
    // Define all Cube states here
    CubeMovingState* movingState = new CubeMovingState(cubeModel);
    CubeIdleState* idleState = new CubeIdleState(cubeModel);

    states.push_back(movingState);
    states.push_back(idleState);

    currentState = movingState;
}