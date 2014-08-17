#include "BoundingBox.h"

BoundingBox::BoundingBox(Model* parentModel)
{
	model = parentModel;
}

BoundingBox::BoundingCube BoundingBox::CalculateBoundingBoxCoordinates()
{
	std::cout << vertexBuffer.size() << std::endl;

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

	//FRONT FACE
	std::vector < glm::vec3 > front_face_1 = { glm::vec3(min_x, min_y, max_z),
		glm::vec3(min_x, min_y, max_z),
		glm::vec3(min_x, max_y, max_z) };

	std::vector < glm::vec3 > front_face_2 = { glm::vec3(max_x, max_y, max_z),
		glm::vec3(min_x, max_y, max_z),
		glm::vec3(min_x, max_y, max_z) };

	//RIGHT FACE
	std::vector < glm::vec3 > right_face_1 = { glm::vec3(max_x, min_y, max_z),
		glm::vec3(max_x, min_y, min_z),
		glm::vec3(max_x, max_y, min_z) };

	std::vector < glm::vec3 > right_face_2 = { glm::vec3(max_x, max_y, min_z),
		glm::vec3(max_x, max_y, max_z),
		glm::vec3(max_x, min_y, max_z) };

	//LEFT FACE
	std::vector < glm::vec3 > left_face_1 = { glm::vec3(min_x, min_y, max_z),
		glm::vec3(min_x, max_y, max_z),
		glm::vec3(min_x, max_y, min_z) };

	std::vector < glm::vec3 > left_face_2 = { glm::vec3(min_x, max_y, min_z),
		glm::vec3(min_x, min_y, min_z),
		glm::vec3(min_x, min_y, max_z) };

	// BACK FACE
	std::vector < glm::vec3 > back_face_1 = { glm::vec3(min_x, min_y, min_z),
		glm::vec3(min_x, max_y, min_z),
		glm::vec3(max_x, max_y, min_z) };

	std::vector < glm::vec3 > back_face_2 = { glm::vec3(min_x, min_y, min_z),
		glm::vec3(max_x, min_y, min_z),
		glm::vec3(max_x, max_y, min_z) };

	// TOP FACE
	std::vector < glm::vec3 > top_face_1 = { glm::vec3(max_x, max_y, max_z),
		glm::vec3(max_x, max_y, min_z),
		glm::vec3(min_x, max_y, min_z) };

	std::vector < glm::vec3 > top_face_2 = { glm::vec3(min_x, max_y, min_z),
		glm::vec3(min_x, max_y, max_z),
		glm::vec3(max_x, max_y, max_z) };

	// DOWN FACE
	std::vector < glm::vec3 > down_face_1 = { glm::vec3(min_x, min_y, max_z),
		glm::vec3(max_x, min_y, max_z),
		glm::vec3(max_x, min_y, min_z) };

	std::vector < glm::vec3 > down_face_2 = { glm::vec3(max_x, min_y, min_z),
		glm::vec3(min_x, min_y, min_z),
		glm::vec3(min_x, min_y, max_z) };

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