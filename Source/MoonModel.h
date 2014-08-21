// Contributors:
//      Oleksandr Dymov

#pragma once
#include "SphereModel.h"
#include "LightModel.h"

class MoonModel : public SphereModel
{
	public:
		MoonModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
		MoonModel(Model * parent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
		~MoonModel(void);
		virtual void Update(float dt);
		virtual void Draw();

	protected:
		virtual void Init(glm::vec3 size);

	private:
		// The vertex format could be different for different types of models
		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 color;
		};

		LightModel* light;

		unsigned int mVertexArrayID;
		unsigned int mVertexBufferID;
		unsigned int numOfVertices;
};

