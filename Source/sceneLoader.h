#pragma once
#ifndef SCENELOADER_H
#define SCENELOADER_H

#include<vector>	
#include"mesh.h"

#include <Importer.hpp>      // C++ importer interface
#include <scene.h>           // Output data structure
#include <postprocess.h>     // Post processing

#define ILUT_USE_OPENGL		// This MUST be defined before calling the DevIL headers or we don't get OpenGL functionality

#include<IL/il.h>
#include<IL/ilu.h>
#include<IL/ilut.h>

//#pragma comment(lib, "DevIL.lib")
//#pragma comment(lib, "ILU.lib")
//#pragma comment(lib, "ILUT.lib")

using namespace std;

class sceneLoader{

	vector<mesh*> meshes;
	void recursiveProcess(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* mesh, const aiScene* scene);
	unsigned int loadTexture(const char* filename);
	void initDevIL(); 

public:
	sceneLoader(const char* filename);
	~sceneLoader();
	void draw(unsigned int programId);
	vector<mesh*>& getMeshes();

};

#endif