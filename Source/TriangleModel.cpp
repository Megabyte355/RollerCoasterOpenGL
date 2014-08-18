// Created to test Ray Casting and AABB collisions
// Created by Kevin Silva on 8/7/14.

#include "TriangleModel.h"
#include "Renderer.h"

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

TriangleModel::TriangleModel(vec3 size)
{
	mParent = nullptr;
	mLightSource = nullptr;
	Init(size);
}

TriangleModel::TriangleModel(Model * parent, vec3 size)
{
	mParent = parent;
	mLightSource = nullptr;
	mGetScalingFromParent = true;
	Init(size);
}

TriangleModel::TriangleModel(Model * parent, bool getScalingFromParent, vec3 size)
{
	mParent = parent;
	mLightSource = nullptr;
	mGetScalingFromParent = getScalingFromParent;
	Init(size);
}

void TriangleModel::Init(vec3 size)
{
	// Create Vertex Buffer for all the verices of the Cube
	vec3 halfSize = size * 0.5f;
											// position,		            normal,			            color
    vertexBuffer[0] = { vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) };
    vertexBuffer[1] = { vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) };
    vertexBuffer[2] = { vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) };

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

	// Set up shader constant defaults
	ka = 0.2f;
	kd = 0.8f;
	ks = 0.2f;
	n = 50.0f;
}

TriangleModel::~TriangleModel()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void TriangleModel::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	// mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second
	Model::Update(dt);
}

void TriangleModel::Draw()
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

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 vertices

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

bool TriangleModel::ParseLine(const std::vector<ci_string> &token)
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

std::vector<Model::Vertex> TriangleModel::GetWorldVertices() {
	glm::mat4 worldMatrix = this->GetWorldMatrix();
    std::vector<Model::Vertex> worldVertexList;

    for (Vertex vertex : vertexBuffer) {
        vertex.position = vec3(worldMatrix * vec4(vertex.position, 1.0f));
        vertex.normal = vec3(worldMatrix * vec4(vertex.normal, 1.0f));
        //color does not need to be modified
        worldVertexList.push_back(vertex);
    }

    return worldVertexList;
}
