// Contributors:
//      Oleksandr Dymov
//      Gary Chang

#pragma once
#include "SphereModel.h"
#include "LightModel.h"

class SunModel : public SphereModel
{
	public:
		SunModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
		SunModel(Model * parent, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
		~SunModel(void);
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

