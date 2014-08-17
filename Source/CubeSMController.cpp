// Contributors:
//      Gary Chang

#include "CubeSMController.h"

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

//void CubeSMController::In()
//{
//
//};
//
//void CubeSMController::Out()
//{
//
//};
//
//void CubeSMController::Execute()
//{
//
//};

void CubeSMController::Init()
{
    // Define all Cube states here
    //states.push_back(new ...);
}