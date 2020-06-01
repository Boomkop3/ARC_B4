#pragma once
#include "GLUnit.h"
#include "GLObject.h"

class LiftableGLUnit :public GLUnit
{
public:
	LiftableGLUnit();
	~LiftableGLUnit();
	void lift();
	void drop();
	void moveToXY(float x, float y);
	void checkTargetPosX();
	void checkTargetPosY();
	void checkTargetPosZ();
	virtual void update(float elapsedTime) override;
	glm::vec3 targetPos = glm::vec3(-1,-1,-1);
	bool isLifted = false;
	bool isMoving = false;
};

