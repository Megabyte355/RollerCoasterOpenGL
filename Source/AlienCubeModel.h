// Contributors:
//      Razvan Alin Cijov

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
#include "Missile.h"

class AlienCubeModel : public Model
{
public:
	// @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
	AlienCubeModel();
	AlienCubeModel(Model * parent);
	virtual ~AlienCubeModel();

	virtual void SetMissile(Missile* mis);
	virtual void Update(float dt);
	virtual void Draw();

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);
    virtual void Init();
	float missileTime;
	Missile* ms;

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
};
