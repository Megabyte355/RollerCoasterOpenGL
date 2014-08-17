// Contributors:
//      Gary Chang

#pragma once

#include "SMController.h"
#include "CubeModelSM.h"
#include "State.h"

class CubeSMController : public SMController
{
public:
    CubeSMController(CubeModelSM* model);
    virtual ~CubeSMController();

    void Update(float dt) override;
    //void In() override;
    //void Out() override;
    //void Execute() override;
    virtual void Init() override;

protected:
    

    CubeModelSM* cubeModel;
    State* currentState;
    std::vector<State*> states;
};
