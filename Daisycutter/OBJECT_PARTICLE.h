#pragma once
#include "Object.h"
#include "objRead.h"

class OBJECT_PARTICLE : public CObject
{
private:
	GLuint vao[6], vbo[6][2];
	glm::mat4 myFactor;

	GLfloat m_fObject_x, m_fObject_y, m_fObject_z;
	GLfloat m_fVelocity_x, m_fVelocity_y, m_fVelocity_z;
	GLfloat color_r, color_g, color_b, color_a;
public:
	static GLfloat data[6][2][2][3][3];
	static int lightPosLocation;
	static int objColorLocation;
	static int lightColorLocation;
public:
	OBJECT_PARTICLE();
	~OBJECT_PARTICLE();

	void PutData(GLfloat Object_x, GLfloat Object_y, GLfloat Object_z);
	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initTexture(GLint ShaderProgram) override;			// 필요치 않을지라도 추가해 줘야 함
	void Update(float fTimeElapsed) override;
	void Render() override;
	void Render(unsigned int modelLocation);

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;
};
