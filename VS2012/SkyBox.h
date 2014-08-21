// Contributors:
//      Shahrad Rezaei

#pragma once

class SkyBox
{
public:
	void main_func();
	void create_cube_map(const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube);
	bool load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name);
};
