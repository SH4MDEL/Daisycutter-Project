#pragma once
#include "Object.h"
#include "objRead.h"

class OBJECT_CLOUD : public CObject
{
private:
	objRead objReader;
	GLint ObjectModel[2];

	GLuint vao, vbo[2];
	unsigned int texture;
	unsigned char* image;

	int objColorLocation;
	int tLocation;

	class CloudData {
	public:
		GLint iObjectStatus;
		GLfloat fObject_x, fObject_y, fObject_z;
		GLfloat fColor_r, fColor_g, fColor_b, fColor_a;
		GLfloat ObjectSpeed;
		glm::mat4 Factor;
	};
	CloudData* pData;

public:
	enum CloudTag {
		Cloud1
		, Cloud2
		, Count
	};

	OBJECT_CLOUD();
	~OBJECT_CLOUD();

	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initTexture(GLint ShaderProgram) override;			// 필요치 않을지라도 추가해 줘야 함
	void Update(float fTimeElapsed) override;
	void Render() override;
	void Render(unsigned int modelLocation);

	void putFactor(glm::mat4 inputFactor) override;
	void putFactor(GLint index, glm::mat4 inputFactor);
	glm::mat4 getFactor() override;
	glm::mat4 getFactor(GLint index);

	void CoordiSet(GLint index);
};

