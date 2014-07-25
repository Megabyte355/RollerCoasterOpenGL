//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "ParsingHelper.h"

#include <vector>

#include <GLM/glm.hpp>


class Model
{
public:
	// @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
	Model();
    Model(Model * p);
	virtual ~Model();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	void Load(ci_istringstream& iss);

	virtual glm::mat4 GetWorldMatrix() const;

	void SetPosition(glm::vec3 position);
	void SetScaling(glm::vec3 scaling);
	void SetRotation(glm::vec3 axis, float angleDegrees);

	glm::vec3 GetPosition() const		{ return mPosition; }
	glm::vec3 GetScaling() const		{ return mScaling; }
	glm::vec3 GetRotationAxis() const	{ return mRotationAxis; }
	float     GetRotationAngle() const	{ return mRotationAngleInDegrees; }

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token) = 0;

	ci_string mName; // The model name is mainly for debugging
	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;

	// @TODO 4 - You may want to add a parent object for the hierarchical modeling
    Model * mParent;
};
