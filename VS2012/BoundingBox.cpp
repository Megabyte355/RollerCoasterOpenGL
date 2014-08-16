#include "BoundingBox.h"

BoundingBox::BoundingBox(Model* parentModel)
{
	model = parentModel;
}

//void BoundingBox::createBoundingBox()
//{
//	std::cout << vertexBuffer.size() << std::endl;
//	if (vertexBuffer.size() == 0)
//	{
//		return;
//	}
//
//	GLfloat vertices[] = {
//		-0.5, -0.5, -0.5, 1.0,
//		 0.5, -0.5, -0.5, 1.0,
//		 0.5,  0.5, -0.5, 1.0,
//		-0.5,  0.5, -0.5, 1.0,
//		-0.5, -0.5,  0.5, 1.0,
//		 0.5,  0.5,  0.5, 1.0,
//		-0.5,  0.5,  0.5, 1.0
//	};
//
//	GLuint vbo_vertices;
//	glGenBuffers(1, &vbo_vertices);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	GLushort elements[] = {
//		0, 1, 2, 3,
//		4, 5, 6, 7,
//		0, 4, 1, 5, 2, 6, 3, 7 };
//
//	GLuint ibo_elements;
//	glGenBuffers(1, &ibo_elements);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	GLfloat min_x, max_x, min_y, max_y, min_z, max_z;
//	min_x = max_x = vertexBuffer[0].position[0];
//	min_y = max_y = vertexBuffer[0].position[1];
//	min_z = max_z = vertexBuffer[0].position[2];
//
//	for (int i = 0; i < vertexBuffer.size(); i++)
//	{
//		if (vertexBuffer[i].position[0] < min_x)
//			min_x = vertexBuffer[i].position[0];
//
//		if (vertexBuffer[i].position[0] > max_x)
//			max_x = vertexBuffer[i].position[0];
//
//		if (vertexBuffer[i].position[1] < min_y)
//			min_y = vertexBuffer[i].position[1];
//
//		if (vertexBuffer[i].position[1] > max_y)
//			max_y = vertexBuffer[i].position[1];
//
//		if (vertexBuffer[i].position[2] < min_z)
//			min_z = vertexBuffer[i].position[2];
//
//		if (vertexBuffer[i].position[2] > max_z)
//			max_z = vertexBuffer[i].position[2];
//	}
//
//	glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
//	glm::vec3 center = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
//	glm::mat4 transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);
//	//TODO: Fix this
//	//glm::mat4 m = GetPositionMatrix()*GetViewMatrix()*GetWorldMatrix() * transform;
//	glm::mat4 m = transform;
//	GLuint BoundingBoxUniformID = glGetUniformLocation(Renderer::GetShaderProgramID(), "BoundingBox");
//	glUniformMatrix4fv(BoundingBoxUniformID, 1, GL_FALSE, glm::value_ptr(m));
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
//	glEnableVertexAttribArray(3);
//	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
//	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
//	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4 * sizeof(GLushort)));
//	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8 * sizeof(GLushort)));
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	glDisableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	glDeleteBuffers(1, &vbo_vertices);
//	glDeleteBuffers(1, &ibo_elements);
//}

///
///
///
void BoundingBox::CalculateBoundingBoxCoordinates()
{
	std::cout << vertexBuffer.size() << std::endl;
	if (vertexBuffer.size() == 0)
	{
		return;
	}

	GLfloat vertices[] = 
	{
		-0.5, -0.5, -0.5, 1.0,
		 0.5, -0.5, -0.5, 1.0,
		 0.5,  0.5, -0.5, 1.0,
		-0.5,  0.5, -0.5, 1.0,
		-0.5, -0.5,  0.5, 1.0,
		 0.5,  0.5,  0.5, 1.0,
		-0.5,  0.5,  0.5, 1.0
	};

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

	glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z) * GetModelScalingFactor();
	glm::vec3 center = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
	glm::mat4 transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);
	
	glm::mat4 m = model->GetWorldMatrixWithoutScaling() * transform;
}

bool BoundingBox::HasObjectCollidedWithAnotherAABB(BoundingBox* OtherBox)
{
	return false;
}

glm::vec3 BoundingBox::GetModelScalingFactor()
{
	Model * currentModel = model;

	glm::vec3 scaling = model->GetScaling();

	if (currentModel->mGetScalingFromParent)
	{
		scaling *= GetModelScalingFactor();
	}

	return scaling;
}