// Contributors:
//      Kevin Silva
//      Shahrad Rezaei

#include "BoundingBox.h"

BoundingBox::BoundingBox(Model* parentModel)
{
	model = parentModel;
}

BoundingBox::BoundingCube BoundingBox::CalculateBoundingBoxCoordinates()
{
	//std::cout << model->vertexBuffer.size() << std::endl;

	if (model->vertexBuffer.size() == 0)
	{
		return BoundingBox::BoundingCube {};
	}

	GLfloat min_x, max_x, min_y, max_y, min_z, max_z;
 	min_x = max_x = model->vertexBuffer.at(0).position[0];
	min_y = max_y = model->vertexBuffer.at(0).position[1];
	min_z = max_z = model->vertexBuffer.at(0).position[2];

	for (int i = 0; i < model->vertexBuffer.size(); i++)
	{
		if (model->vertexBuffer.at(i).position[0] < min_x)
			min_x = model->vertexBuffer.at(i).position[0];

		if (model->vertexBuffer.at(i).position[0] > max_x)
			max_x = model->vertexBuffer.at(i).position[0];

		if (model->vertexBuffer.at(i).position[1] < min_y)
			min_y = model->vertexBuffer.at(i).position[1];

		if (model->vertexBuffer.at(i).position[1] > max_y)
			max_y = model->vertexBuffer.at(i).position[1];

		if (model->vertexBuffer.at(i).position[2] < min_z)
			min_z = model->vertexBuffer.at(i).position[2];

		if (model->vertexBuffer.at(i).position[2] > max_z)
			max_z = model->vertexBuffer.at(i).position[2];
	}

	glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z) * GetModelScalingFactor();
	glm::mat4 worldMatrix = model->GetWorldMatrix();

	//FRONT FACE
	std::vector < glm::vec3 > front_face_1 = 
	{   glm::vec3(worldMatrix * glm::vec4(min_x, min_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, min_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, max_z, 1.0)) };

	std::vector < glm::vec3 > front_face_2 = { 
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, max_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, max_z, 1.0)) };

	//RIGHT FACE
	std::vector < glm::vec3 > right_face_1 = { 
		glm::vec3(worldMatrix * glm::vec4(max_x, min_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, min_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, min_z, 1.0)) };

	std::vector < glm::vec3 > right_face_2 = { 
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, min_y, max_z, 1.0)) };

	//LEFT FACE
	std::vector < glm::vec3 > left_face_1 = { 
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, max_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, max_y, min_z, 1.0)) };

	std::vector < glm::vec3 > left_face_2 = { 
		glm::vec3(worldMatrix * glm::vec4(min_x, max_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, max_z, 1.0)) };

	// BACK FACE
	std::vector < glm::vec3 > back_face_1 = { 
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, max_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, min_z, 1.0)) };

	std::vector < glm::vec3 > back_face_2 = { 
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, min_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, min_z, 1.0)) };

	// TOP FACE
	std::vector < glm::vec3 > top_face_1 = { 
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, max_y, min_z, 1.0)) };

	std::vector < glm::vec3 > top_face_2 = { 
		glm::vec3(worldMatrix * glm::vec4(min_x, max_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, max_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, max_y, max_z, 1.0)) };

	// DOWN FACE
	std::vector < glm::vec3 > down_face_1 = { 
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, min_y, min_z, 1.0)) };

	std::vector < glm::vec3 > down_face_2 = { 
		glm::vec3(worldMatrix * glm::vec4(max_x, min_y, min_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(max_x, min_y, max_z, 1.0)),
		glm::vec3(worldMatrix * glm::vec4(min_x, min_y, max_z, 1.0)) };

	BoundingBox::BoundingCube bcube = {
			{ front_face_1, front_face_2 },
			{ right_face_1, right_face_2 },
			{ left_face_1, left_face_2 },
			{ back_face_1, back_face_2 },
			{ top_face_1, top_face_2 },
			{ down_face_1, down_face_2 } };

	return bcube;
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