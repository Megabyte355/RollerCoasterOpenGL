// Created to test Ray Casting and AABB collisions
// Created by Kevin Silva on 8/7/14.

#pragma once

#include "Model.h"
#include "LightModel.h"
#include <vector>

class TriangleModel : public Model
{

private:

	Vertex vertexBuffer[3];

public:
	// @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
	TriangleModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	TriangleModel(Model * parent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	TriangleModel(Model * parent, bool getScalingFromParent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~TriangleModel();

	virtual void Update(float dt);
	virtual void Draw();

    std::vector<Vertex> GetWorldVertices();

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);
	virtual void Init(glm::vec3 size);


};
