// Contributors:
//      Shahrad Rezaei

#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <cstdlib>
#include <cstdio>
#include "SkyBox.h"
#include "stb_image.h"


float points[] = {
	-10.0f, 10.0f, -10.0f,
	-10.0f, -10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,
	10.0f, 10.0f, -10.0f,
	-10.0f, 10.0f, -10.0f,

	-10.0f, -10.0f, 10.0f,
	-10.0f, -10.0f, -10.0f,
	-10.0f, 10.0f, -10.0f,
	-10.0f, 10.0f, -10.0f,
	-10.0f, 10.0f, 10.0f,
	-10.0f, -10.0f, 10.0f,

	10.0f, -10.0f, -10.0f,
	10.0f, -10.0f, 10.0f,
	10.0f, 10.0f, 10.0f,
	10.0f, 10.0f, 10.0f,
	10.0f, 10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,

	-10.0f, -10.0f, 10.0f,
	-10.0f, 10.0f, 10.0f,
	10.0f, 10.0f, 10.0f,
	10.0f, 10.0f, 10.0f,
	10.0f, -10.0f, 10.0f,
	-10.0f, -10.0f, 10.0f,

	-10.0f, 10.0f, -10.0f,
	10.0f, 10.0f, -10.0f,
	10.0f, 10.0f, 10.0f,
	10.0f, 10.0f, 10.0f,
	-10.0f, 10.0f, 10.0f,
	-10.0f, 10.0f, -10.0f,

	-10.0f, -10.0f, -10.0f,
	-10.0f, -10.0f, 10.0f,
	10.0f, -10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,
	-10.0f, -10.0f, 10.0f,
	10.0f, -10.0f, 10.0f
};

void SkyBox::main_func()
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
};

void SkyBox::create_cube_map(const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube)
{
	// generate a cube-map texture to hold all the sides
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);

	// load each image and copy into a side of the cube-map texture
	assert(load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front));
	assert(load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back));
	assert(load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top));
	assert(load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom));
	assert(load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left));
	assert(load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right));
	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool SkyBox::load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int x, y, n;
	int force_channels = 4;
	unsigned char*  image_data = stbi_load(file_name, &x, &y, &n, force_channels);
	if (!image_data) 
	{
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}

	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0)
	{
		fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name);
	}

	// copy image data into 'target' side of cube map
	glTexImage2D(side_target, 0, GL_RGBA, x, y,	0, GL_RGBA,	GL_UNSIGNED_BYTE, image_data);
	free(image_data);
	return true;
}