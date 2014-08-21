// Contributors:
//      Razvan Alin Cijov

#pragma once
#include "Model.h"
#include "TankModel.h"
#include "vector"

class Missile : public Model
{
public:
	Missile(void);
    Missile(TankModel* tank);
	~Missile(void);
	void AddMissile(glm::vec3 p);
    void Init();
	
	virtual void Update(float dt);
	virtual void Draw();

protected:
	void Add(glm::vec3 position);
	void Trajectory(BSpline* sp);
    virtual bool ParseLine(const std::vector<ci_string> &token);
	CubeModel* GetCube() { return cube; }

private:
    float speed;
	CubeModel* cube;

};
