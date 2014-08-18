// Contributors:
//      Gary Chang

#include "State.h"

State::State()
{
}

State::~State()
{
}

bool State::IsExpired()
{
    // default expiration condition
    return duration <= 0.0f;
}