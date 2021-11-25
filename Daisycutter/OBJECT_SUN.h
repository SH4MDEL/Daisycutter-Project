#pragma once
#include "Object.h"
#include "objRead.h"

class OBJECT_SUN : public CObject
{
private:
	GLuint vao[3], vbo[3][2];
	int objColorLocation;
	glm::mat4 myFactor;

public:
	static objRead objReader;
	static GLint object;

	OBJECT_SUN();
	~OBJECT_SUN();

	void OnCreate() override;
	void initBuffer(GLint s_program) override;
	void Update(float fTimeElapsed) override;
	void Render() override;

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;
};

