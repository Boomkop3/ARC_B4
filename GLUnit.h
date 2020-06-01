#pragma once

class GLObject;

class GLUnit
{
protected:
	GLObject* glObject;
public:
	GLUnit();
	~GLUnit();

	virtual void update(float elapsedTime) {};
	void setGLObject(GLObject* glObject);
};

