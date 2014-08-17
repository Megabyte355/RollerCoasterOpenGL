// Contributors:
//      Gary Chang

#pragma once

#include "Model.h"

class State
{
public:
    State(Model* model);
    virtual ~State();

    virtual void In() = 0;
    virtual void Out() = 0;
    virtual void Execute() = 0;

protected:
    virtual void Init() = 0;

    Model* model;
};
