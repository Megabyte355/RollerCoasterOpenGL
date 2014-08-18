// Contributors:
//      Gary Chang

#pragma once

#include "Model.h"
#include "State.h"
#include "CubeModelSM.h"

class CubeMovingState : public State
{
public:
    CubeMovingState(CubeModelSM* model);
    virtual ~CubeMovingState();

    virtual void In() override;
    virtual void Out() override;
    virtual void Execute(float dt) override;
    bool IsExpired() override;

protected:
    virtual void Init();

    CubeModelSM* cubeModel;
};
