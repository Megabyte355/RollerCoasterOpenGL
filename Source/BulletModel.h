// Contributors:
//      Gary Chang
//	    Oleksandr Dymov

//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "CubeModel.h"

class BulletModel : public CubeModel
{
public:
	BulletModel(glm::vec3 size = glm::vec3(0.5f, 0.5f, 0.5f));
	BulletModel(Model * parent, glm::vec3 size = glm::vec3(0.5f, 0.5f, 0.5f));
	BulletModel(Model * parent, bool getScalingFromParent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	~BulletModel();

    void Update(float dt) override;

    void Init(glm::vec3 size);
    void SetCoordinates(glm::vec3 position, glm::vec3 direction);
    bool IsAlive();

protected:
    float lifetime;
    float bulletSpeed;
    glm::vec3 mForward;
};
