#pragma once

#ifndef MESHDATA_H
#define MESHDATA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;
using namespace std;

struct vertexData{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 color;
	glm::vec2 UV;
};

struct textureData{
	unsigned int id;
	unsigned int type;
};


#endif