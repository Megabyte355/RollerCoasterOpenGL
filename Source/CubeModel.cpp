//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "CubeModel.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/common.hpp>

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

CubeModel::CubeModel(vec3 size)
{
	mParent = nullptr;
	mLightSource = nullptr;
	Init(size);
}

CubeModel::CubeModel(Model * parent, vec3 size)
{
	mParent = parent;
	mLightSource = nullptr;
	mGetScalingFromParent = true;
	Init(size);
}

CubeModel::CubeModel(Model * parent, bool getScalingFromParent, vec3 size)
{
	mParent = parent;
	mLightSource = nullptr;
	mGetScalingFromParent = getScalingFromParent;
	Init(size);
}

void CubeModel::Init(vec3 size)
{
	// Create Vertex Buffer for all the verices of the Cube
	vec3 halfSize = size * 0.5f;

	vertexBuffer = {  // position,                normal,                  color
			{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) }, //left - red
			{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
			{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },

			{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
			{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
			{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },

			{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) }, // far - blue
			{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },
			{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },

			{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },
			{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },
			{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },

			{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) }, // bottom - turquoise
			{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
			{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },

			{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
			{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
			{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },

			{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) }, // near - green
			{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
			{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },

			{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
			{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
			{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },

			{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) }, // right - purple
			{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
			{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },

			{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
			{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
			{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },

			{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) }, // top - yellow
			{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
			{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },

			{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
			{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
			{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) }
	};

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), &vertexBuffer.front(), GL_STATIC_DRAW);

	// Set up shader constant defaults
	ka = 0.2f;
	kd = 0.8f;
	ks = 0.2f;
	n = 50.0f;
}

CubeModel::~CubeModel()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void CubeModel::draw_bbox()
{
	std::cout << vertexBuffer.size() << std::endl;
	if (vertexBuffer.size() == 0)
	{
		return;
	}

	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5, 0.5, -0.5, 1.0,
		-0.5, 0.5, -0.5, 1.0,
		-0.5, -0.5, 0.5, 1.0,
		0.5, 0.5, 0.5, 1.0,
		-0.5, 0.5, 0.5, 1.0
	};

	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5, 2, 6, 3, 7 };

	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLfloat min_x, max_x, min_y, max_y, min_z, max_z;
	min_x = max_x = vertexBuffer[0].position[0];
	min_y = max_y = vertexBuffer[0].position[1];
	min_z = max_z = vertexBuffer[0].position[2];

	for (int i = 0; i < vertexBuffer.size(); i++)
	{
		if (vertexBuffer[i].position[0] < min_x)
			min_x = vertexBuffer[i].position[0];

		if (vertexBuffer[i].position[0] > max_x)
			max_x = vertexBuffer[i].position[0];

		if (vertexBuffer[i].position[1] < min_y)
			min_y = vertexBuffer[i].position[1];

		if (vertexBuffer[i].position[1] > max_y)
			max_y = vertexBuffer[i].position[1];

		if (vertexBuffer[i].position[2] < min_z)
			min_z = vertexBuffer[i].position[2];

		if (vertexBuffer[i].position[2] > max_z)
			max_z = vertexBuffer[i].position[2];
	}

	glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
	glm::vec3 center = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
	glm::mat4 transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);
	//TODO: Fix this
	//glm::mat4 m = mesh->object2world * transform;
	GLuint BoundingBoxUniformID = glGetUniformLocation(Renderer::GetShaderProgramID(), "BoundingBox");
	glUniformMatrix4fv(BoundingBoxUniformID, 1, GL_FALSE, glm::value_ptr(m));

	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4 * sizeof(GLushort)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8 * sizeof(GLushort)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);
}

void CubeModel::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	// mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second
	Model::Update(dt);
}

void CubeModel::Draw()
{
	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	if (mLightSource != nullptr)
	{
		mLightSource->SetShaderConstants(ka, kd, ks, n);
	}

	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(0,				// attribute. No particular reason for 0, but must match the layout in the shader.
		3,				// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
		);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
		);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(2 * sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
		);

	draw_bbox();

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

bool CubeModel::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}
