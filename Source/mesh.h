#pragma once

#ifndef MESH_H
#define MESH_H

#include<iostream>
#include<GL/glew.h>
#include<vector>
#include<string>
#include"meshData.h"

class mesh{
	vector<vertexData> data;
	vector<textureData> textures;
	vector<unsigned int> indices;
	unsigned int VBO;
	unsigned int IND;

public:
	mesh(vector<vertexData>* vd, vector<unsigned int>* id, vector<textureData>* td=NULL); 
	~mesh();

	void draw(unsigned int programId);

};

#endif