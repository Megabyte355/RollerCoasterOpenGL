#pragma once
#include "Model.h"
#include "TankModel.h"
#include "vector"

class Missile : public Model
{
public:
    Missile(TankModel* tank);
	~Missile(void);
	void AddMissile(glm::vec3 p);
    void Init();
	
	virtual void Update(float dt);
	virtual void Draw();

protected:
	void Add(glm::vec3 position);
	void Trajectory();
    virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    float speed;
	BSpline* spline;
};
