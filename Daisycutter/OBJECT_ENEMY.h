#pragma once
#include "Object.h"
#include "objRead.h"

class OBJECT_ENEMY : public CObject
{
private:
	GLuint vao, vbo[3];
	unsigned int texture;
	unsigned char* image;

	int objColorLocation;
	int tLocation;

	class EnemyData {
	public:
		GLint iObjectStatus;
		GLfloat fObject_x, fObject_y, fObject_z;
		glm::mat4 Factor;
	};
	EnemyData* pData;

	GLdouble m_dBPM;
	GLint iNowIndex;
public:
	enum EnemyStatusTag {
		NullState
		, ActiveState
		, InvincibleState
		, DieState
		, Count
	};
	static objRead objReader;
	static GLint ObjectMedel;

	OBJECT_ENEMY();
	OBJECT_ENEMY(GLdouble BPM);
	~OBJECT_ENEMY();

	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initTexture(GLint ShaderProgram) override;			// 필요치 않을지라도 추가해 줘야 함
	void Update(float fTimeElapsed) override;
	void Render() override;
	void Render(unsigned int modelLocation);

	void EnemyCreate(GLint Location);
	void EnemyAttacked();
	void EnemyRemove(GLint index);
	GLfloat getOz(GLint index);

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;
};

