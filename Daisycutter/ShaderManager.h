#pragma once
#include "stdafx.h"
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"

class ShaderManager
{
public:
	enum ShaderTag {
		BitmapShader
		, NonBitmapShader
		, ManualShader
		, Count
	};
private:
	const char ShaderName[Count][2][32] = {
		{"SHADER\\bitmap_vertex.glsl", "SHADER\\bitmap_fragment.glsl"},
		{"SHADER\\nonbitmap_vertex.glsl", "SHADER\\nonbitmap_fragment.glsl"},
		{"SHADER\\manual_vertex.glsl", "SHADER\\manual_fragment.glsl"}
	};

	GLchar* vertexSource, *fragmentSource; //--- �ҽ��ڵ� ���� ����
	GLuint vertexShader, fragmentShader; //--- ���̴� ��ü

	GLint* m_ShaderProgram;
public:
	ShaderManager();
	void BindShader();
	GLint GetShader(ShaderTag tag);
};

