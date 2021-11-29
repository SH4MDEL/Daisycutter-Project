#pragma once
#include "stdafx.h"
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"

class ShaderManager
{
public:
	enum ShaderTag {
		BasicShader
		, PlayerShader
		, Count
	};
private:
	const char ShaderName[Count][2][32] = {
		{"vertex.glsl", "fragment.glsl"},
		{"player_vertex.glsl", "player_fragment.glsl"}
	};

	GLchar* vertexSource, *fragmentSource; //--- �ҽ��ڵ� ���� ����
	GLuint vertexShader, fragmentShader; //--- ���̴� ��ü

	GLint* m_ShaderProgram;
public:
	ShaderManager();
	void BindShader();
	GLint GetShader(ShaderTag tag);
};

