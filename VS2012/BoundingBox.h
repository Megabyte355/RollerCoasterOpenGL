#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/common.hpp>
#include "../../Source/Model.h"
#include <vector>
#include "../../Source/CubeModel.h"

class BoundingBox
{
public:
	BoundingBox(Model* parent);
	void CalculateBoundingBoxCoordinates();
	bool HasObjectCollidedWithAnotherAABB(BoundingBox* OtherBox);

private:
	glm::vec3 GetModelScalingFactor();

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
	std::vector<Vertex> vertexBuffer;
	float scalingFactor;
	Model* model;
};