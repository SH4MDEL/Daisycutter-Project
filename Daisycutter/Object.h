#pragma once
#include "stdafx.h"

class CObject
{
protected:
	CObject();
	~CObject();

	virtual void OnCreate() = 0;
	virtual void initBuffer(GLint s_program) = 0;
	virtual void initTexture(GLint s_program) = 0;
	virtual void Update(float fTimeElapsed) = 0;
	virtual void Render() = 0;

	virtual void putFactor(glm::mat4 inputFactor) = 0;	// �̵� ���� ����. (�ʱⰪ�� �ݵ�� ����)
	virtual glm::mat4 getFactor() = 0;					// �̵� ���� ��ȯ.

	GLint s_program;
};

