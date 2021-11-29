#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	m_ShaderProgram = new GLint[ShaderTag::Count];
}

void ShaderManager::BindShader()
{
	for (int i = 0; i < ShaderTag::Count; i++) {
		make_vertexShaders(vertexSource, vertexShader, ShaderName[i][0]);
		make_fragmentShaders(fragmentSource, fragmentShader, ShaderName[i][1]);
		m_ShaderProgram[i] = make_shaderProgram(vertexShader, fragmentShader);
	}
}

GLint ShaderManager::GetShader(ShaderTag tag)
{
	return m_ShaderProgram[tag];
}
