// Contributors:
//      Shahrad Rezaei

//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "TexturedCube.h"
#include "Renderer.h"
#include <iostream>

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

TexturedCube::TexturedCube(vec3 size)
{
    mParent = nullptr;
    mLightSource = nullptr;
    mGetScalingFromParent = false;
	mTexturePath = "../Source/Textures/uvtemplate.bmp";
    Init(size);
}

TexturedCube::TexturedCube(Model * parent, vec3 size)
{
    mParent = parent;
    mLightSource = nullptr;
	mGetScalingFromParent = true;
	mTexturePath = "../Source/Textures/uvtemplate.bmp";
    Init(size);
}

TexturedCube::TexturedCube(Model * parent, bool getScalingFromParent, vec3 size)
{
    mParent = parent;
    mLightSource = nullptr;
    mGetScalingFromParent = getScalingFromParent;
	mTexturePath = "../Source/Textures/uvtemplate.bmp";
    Init(size);
}

/// <summary> Overloaded constructor for the CubeModel function, accepting a texture path to load onto the cube.</summary>
/// <param name = 'texturePath'>The path to the texture.</param>
TexturedCube::TexturedCube(Model * parent, bool getScalingFromParent, ci_string texturePath, vec3 size)
{
	mParent = parent;
	mLightSource = nullptr;
	mGetScalingFromParent = getScalingFromParent;
	mTexturePath = texturePath;
	Init(size);
}

void TexturedCube::Init(vec3 size)
{
	// Load the texture using any two methods
	Texture = BitmapLoader("../Source/Textures/uvtemplate.bmp");

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(Renderer::GetShaderProgramID(), "cubeTexture");

    // Create Vertex Buffer for all the verices of the Cube
	vec3 halfSize = size * 0.5f;
	
	vertexBuffer = {  // position,                normal,                  color
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) }, //left - red
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 1.0f, 0.0f) }, // far - blue
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) }, // bottom - turquoise
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
																
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) }, // near - green
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) }, // right - purple
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) }, // top - yellow
								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) }
						};

	static const GLfloat g_uv_buffer_data[] =
{
		-1,-1,
		-1, 1,
		 1, 1,
		   
		-1,-1,
		 1, 1,
		 1,-1,
		   
		 1, 1,
		-1,-1,
		-1, 1,
		   
		 1, 1,
		 1,-1,
		-1,-1,
		   
		 1, 1,
		-1,-1,
		 1,-1,
		  
		 1, 1,
		-1, 1,
		-1,-1,
		   
		-1, 1,
		-1,-1,
		 1,-1,
		   
		 1, 1,
		-1, 1,
		 1,-1,
		
		  1, 1,
		 -1,-1,
		  1,-1,
		
		 -1,-1,
		  1, 1,
		 -1, 1,
		
		 1,  1,
		 1, -1,
		-1, -1,
					 
		 1,  1,
		-1, -1,
		-1,  1
	};

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), &vertexBuffer.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    // Set up shader constant defaults
    ka = 1;
    kd = 0;
    ks = 0;
    n = 1;
}

TexturedCube::~TexturedCube()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void TexturedCube::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	// mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second
    Model::Update(dt);
}

void TexturedCube::Draw()
{
	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);

    GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform"); 
    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

    if(mLightSource != nullptr)
    {
        mLightSource->SetShaderConstants(ka, kd, ks, n);
    }

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	0,				// attribute. No particular reason for 0, but must match the layout in the shader.
							3,				// size
							GL_FLOAT,		// type
							GL_FALSE,		// normalized?
							sizeof(Vertex), // stride
							(void*)0        // array buffer offset
						);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	1,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
						);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	2,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*) (2* sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
						);

	// 4th attribute buffer : UVs
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		3,                                
		2,                                
		GL_FLOAT,                         
		GL_FALSE,                         
		0,                                
		(void*)0                          
		);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void TexturedCube::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while (std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		std::istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		std::istream_iterator<ci_string, char, ci_char_traits> end;
		std::vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			fprintf(stderr, "Error loading scene file... token:  %s!", token[0]);
			getchar();
			exit(-1);
		}
	}
}

bool TexturedCube::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		if (token[0] == "texture_path")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			Texture = BitmapLoader(token[2].c_str());
			return true;
		}

		if (token[0] == "Ka")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			ka = ::atof(token[2].c_str());
			return true;
		}

		if (token[0] == "Kd")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			kd == ::atof(token[2].c_str());
			return true;
		}

		if (token[0] == "Ks")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			ks = ::atof(token[2].c_str());
			return true;
		}

		if (token[0] == "n")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			n = ::atof(token[2].c_str());
			return true;
		}

		return Model::ParseLine(token);
	}
}

GLuint TexturedCube::BitmapLoader(ci_string file_path)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width;
	unsigned int height;
	unsigned int imageSize;
	unsigned char *data;

	bool isValid = true;

	FILE * file = fopen(file_path.c_str(), "rb");
	if (!file)
		printf("Image %s could not be loaded", file_path);

	if (fread(header, 1, 54, file) != 54)
		return BitmapLoader("../Source/Textures/uvtemplate.bmp");
	
	if (header[0] != 'B' || header[1] != 'M')
		return BitmapLoader("../Source/Textures/uvtemplate.bmp");

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = width*height * 3;
	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	GLuint textureID;
	
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}
