// Contributors:
//      Gary Chang

//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Model.h"
#include "LightModel.h"
class CubeSMController;

class CubeModelSM : public Model
{
public:
    // @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
    CubeModelSM(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
    CubeModelSM(Model * parent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
    CubeModelSM(Model * parent, bool getScalingFromParent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
    virtual ~CubeModelSM();

    virtual void Update(float dt);
    virtual void Draw();

protected:
    virtual bool ParseLine(const std::vector<ci_string> &token);
    virtual void Init(glm::vec3 size);

private:
    // The vertex format could be different for different types of models
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };

    CubeSMController* stateController;
};
