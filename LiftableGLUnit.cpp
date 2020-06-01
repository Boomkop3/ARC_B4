#include "LiftableGLUnit.h"

#define INC_DEC_Y 0.1f
#define INC_DEC_XZ 0.1f

LiftableGLUnit::LiftableGLUnit()
{
}

LiftableGLUnit::~LiftableGLUnit()
{
}

void LiftableGLUnit::lift()
{
	if (!isMoving)
		if (!isLifted) {
			this->targetPos.y = this->glObject->position.y + 2.f;
			isLifted = true;
			isMoving = true;
		}
}

void LiftableGLUnit::drop()
{
	if (!isMoving)
		if (isLifted) {
			this->targetPos.y = this->glObject->position.y - 2.f;
			isLifted = false;
			isMoving = true;
		}
}

void LiftableGLUnit::moveToXY(float x, float y) {
	this->targetPos.x = x;
	this->targetPos.z = y;
}

void LiftableGLUnit::checkTargetPosX() {
	if (this->targetPos.x != -1) {
		if (this->targetPos.x != this->glObject->position.x) {
			if (std::abs(this->targetPos.x - this->glObject->position.x) > INC_DEC_XZ) {
				if (this->glObject->position.x > this->targetPos.x)
					this->glObject->position.x -= INC_DEC_XZ;
				else
					this->glObject->position.x += INC_DEC_XZ;
			}
			else {
				this->glObject->position.x = this->targetPos.x;
				this->targetPos.x = -1;
			}
		}
	}
}

void LiftableGLUnit::checkTargetPosY() {
	if (this->targetPos.y != -1) {
		if (this->targetPos.y != this->glObject->position.y) {
			if (std::abs(this->targetPos.y - this->glObject->position.y) > INC_DEC_Y) {
				if (this->glObject->position.y > this->targetPos.y)
					this->glObject->position.y -= INC_DEC_Y;
				else if (this->glObject->position.y < this->targetPos.y)
					this->glObject->position.y += INC_DEC_Y;
			}
			else {
				this->glObject->position.y = this->targetPos.y;
				this->targetPos.y = -1;
			}
		}
	}
	else isMoving = false;
}

void LiftableGLUnit::checkTargetPosZ() {
	if (this->targetPos.z != -1) {
		if (this->targetPos.z != this->glObject->position.z) {
			if (std::abs(this->targetPos.z - this->glObject->position.z) > INC_DEC_XZ) {
				if (this->glObject->position.z > this->targetPos.z)
					this->glObject->position.z -= INC_DEC_XZ;
				else if (this->glObject->position.z < this->targetPos.z)
					this->glObject->position.z += INC_DEC_XZ;
			}
			else {
				this->glObject->position.z = this->targetPos.z;
				this->targetPos.z = -1;
			}
		}
	}
}

void LiftableGLUnit::update(float elapsedTime)
{
	if (this->targetPos.y >= this->glObject->position.y || (this->targetPos.x==-1 || this->targetPos.z==-1)) {
		checkTargetPosY();
	}
	if (this->targetPos.y <= this->glObject->position.y || (this->targetPos.y==-1)) {
		checkTargetPosX();
		checkTargetPosZ();
	}
}
