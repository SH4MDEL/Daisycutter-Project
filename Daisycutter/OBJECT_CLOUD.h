#pragma once
#include "Object.h"
#include "objRead.h"

class OBJECT_CLOUD : public CObject
{
private:
	objRead objReader;
	GLint ObjectModel;

	GLuint vao, vbo[3];
	unsigned int texture;
	unsigned char* image;
	glm::mat4 myFactor;

	int objColorLocation;
	int tLocation;


	GLfloat object_x, object_y, object_z;
	GLfloat ObjectSpeed;

	GLint CloudStatus;
public:
	enum CloudTag {
		Cloud1
		, Cloud2
		, Cloud3
		, Cloud4
		, Count
	};

	OBJECT_CLOUD();
	~OBJECT_CLOUD();

	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initTexture(GLint ShaderProgram) override;			// 필요치 않을지라도 추가해 줘야 함
	void Update(float fTimeElapsed) override;
	void Render() override;

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;

	void CoordiSet();
};

