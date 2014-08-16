
#include"sceneLoader.h"
#include<sstream>

sceneLoader::sceneLoader(const char* filename)
{
	Assimp::Importer importer;
	//Initialize DevIL
	initDevIL(); 
	
	const aiScene* scene=importer.ReadFile(filename, 
											aiProcess_GenSmoothNormals|
											aiProcess_Triangulate|
											aiProcess_CalcTangentSpace|
											aiProcess_FlipUVs);

	if(scene->mFlags==AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{ 
      fprintf( stderr, "Couldn't load model, Error Importing Asset" );	   
	  return;
	} 

	recursiveProcess(scene->mRootNode, scene);

}

sceneLoader::~sceneLoader()
{
	for(std::size_t i=0; i<meshes.size(); i++)
		delete meshes[i];
}

void sceneLoader::initDevIL()
{
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}

void sceneLoader::recursiveProcess(aiNode* node, const aiScene* scene)
{
	//process
	for(std::size_t i=0; i<node->mNumMeshes;i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}

	//recursion
	for(std::size_t i=0; i<node->mNumChildren; i++)
	{
		recursiveProcess(node->mChildren[i], scene);
	}
}

void sceneLoader::processMesh(aiMesh* cmesh, const aiScene* scene)
{
	vector<vertexData> data;
	vector<unsigned int> indices;
	vector<textureData> textures;
	aiColor4D col;
	aiMaterial* mat = scene->mMaterials[cmesh->mMaterialIndex];
	aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &col); 
	glm::vec3 defaultColor(col.r, col.g, col.b);

	for(std::size_t i=0; i<cmesh->mNumVertices; i++)
	{
		vertexData tmp;
		
		//position
		tmp.position = glm::vec3(cmesh->mVertices[i].x,  cmesh->mVertices[i].y, cmesh->mVertices[i].z);
		
		//normals
		tmp.normal = glm::vec3(cmesh->mNormals[i].x,  cmesh->mNormals[i].y, cmesh->mNormals[i].z);

		//tangents
		if(cmesh->mTangents)
			tmp.tangent = glm::vec3(cmesh->mTangents[i].x,  cmesh->mTangents[i].y, cmesh->mTangents[i].z);
		else
			tmp.tangent = glm::vec3(1,0,0);

		//colors
		if(cmesh->mColors[0])
			tmp.color = glm::vec3(cmesh->mColors[0][i].r,  cmesh->mColors[0][i].g, cmesh->mColors[0][i].b);
		else
			tmp.color = defaultColor;

		//UVs
		if(cmesh->mTextureCoords[0])
			tmp.UV = glm::vec2(cmesh->mTextureCoords[0][i].x,  cmesh->mTextureCoords[0][i].y);
		else
			tmp.UV = glm::vec2(0,0);
		data.push_back(tmp);
	}

	for(std::size_t i=0; i<cmesh->mNumFaces; i++)
	{
		aiFace face = cmesh->mFaces[i];
		for(std::size_t j=0; j<face.mNumIndices;j++) //0...2
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//handle textures
	for(std::size_t i=0; i<mat->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString str;
		mat->GetTexture(aiTextureType_DIFFUSE, i, &str);
		textureData tmp;
		tmp.id = loadTexture(str.C_Str());
		tmp.type = 0;	//Index for Diffuse Map
		textures.push_back(tmp);
	}

	meshes.push_back(new mesh(&data, &indices, &textures));
}
	
unsigned int sceneLoader::loadTexture(const char* filename)
{
	ILuint imageID;				// Create an image ID as a ULuint
 
	GLuint textureID;			// Create a texture ID as a GLuint
 
	ILboolean success;			// Create a flag to keep track of success/failure
 
	ILenum error;				// Create a flag to keep track of the IL error state
 
	ilGenImages(1, &imageID); 		// Generate the image ID
 
	ilBindImage(imageID); 			// Bind the image
 
	std::stringstream sstm;
	sstm << "../Source/Models/alien/" << filename;
	success = ilLoadImage((const ILstring) &sstm.str()[0]); 	// Load the image file
 
	// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
	/*	ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}*/

		// Convert the image into a suitable format to work with
		// NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
 
		// Quit out if we failed the conversion
		if (!success)
		{
			error = ilGetError();
			std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
			exit(-1);
		}
 
		// Generate a new texture
		glGenTextures(1, &textureID);
 
		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_2D, textureID);
 
		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 
		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 
		// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
					 0,				// Pyramid level (for mip-mapping) - 0 is the top level
					 ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
					 ilGetInteger(IL_IMAGE_WIDTH),	// Image width
					 ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
					 0,				// Border width in pixels (can either be 1 or 0)
					 ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
					 GL_UNSIGNED_BYTE,		// Image data type
					 ilGetData());			// The actual image data itself
 	}
  	else // If we failed to open the image file in the first place...
  	{
		error = ilGetError();
		std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		exit(-1);
  	}
 
 	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.
 
	std::cout << "Texture creation successful." << std::endl;
 
	return textureID; // Return the GLuint to the texture so you can use it!
}

void sceneLoader::draw(unsigned int programId)
{
	for(std::size_t i=0; i<meshes.size();i++)
		meshes[i]->draw(programId);
}

vector<mesh*>& sceneLoader::getMeshes()
{
	return meshes;
}