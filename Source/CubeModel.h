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

class CubeModel : public Model
{

public:
	// @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
	CubeModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	CubeModel(Model * parent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	CubeModel(Model * parent, bool getScalingFromParent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	CubeModel(Model * parent, bool getScalingFromParent, ci_string texturePath, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~CubeModel();

	virtual void Update(float dt);
	virtual void Draw();

protected:
	ci_string mTexturePath;
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

	GLuint TextureID;
	GLuint Texture;
};
