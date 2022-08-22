#include "OBJECT_CLOUD.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

OBJECT_CLOUD::OBJECT_CLOUD()
{
	OnCreate();
}

OBJECT_CLOUD::~OBJECT_CLOUD()
{
	delete[] pData;
}

void OBJECT_CLOUD::OnCreate()
{
	char Text[100];

	for (int i = 0; i < 2; i++) {
		sprintf(Text, "GRAPHIC\\OBJECT\\CLOUD\\CLOUD%d.obj", i);
		ObjectModel[i] = objReader.loadObj_normalize_center(Text);
	}
	pData = new CloudData[MAX_CLOUD_CREATE];
	for (int i = 0; i < MAX_CLOUD_CREATE; i++) {
		pData[i].fObject_x = RandomDevice::GetRandomGLfloat(-10.0f, 10.0f);
		pData[i].fObject_y = RandomDevice::GetRandomGLfloat(-10.0f, 10.0f);
		pData[i].fObject_z = RandomDevice::GetRandomGLfloat(-150.0f, 10.0f);
		pData[i].ObjectSpeed = RandomDevice::GetRandomGLfloat(5.0f, 6.0f);
		pData[i].iObjectStatus = RandomDevice::GetRandomGLint(0, 1);

		pData[i].fColor_r = pData[i].fColor_g = pData[i].fColor_b = RandomDevice::GetRandomGLfloat(0.7f, 0.9f);
		pData[i].fColor_a = 0.3f;
	}
}

void OBJECT_CLOUD::CoordiSet(GLint index)
{
	pData[index].fObject_x = RandomDevice::GetRandomGLfloat(-10.0f, 10.0f);
	pData[index].fObject_y = RandomDevice::GetRandomGLfloat(-10.0f, 10.0f);
	pData[index].fObject_z = -150.0f;
	pData[index].ObjectSpeed = RandomDevice::GetRandomGLfloat(5.0f, 6.0f);
	pData[index].fColor_r = pData[index].fColor_g = pData[index].fColor_b = RandomDevice::GetRandomGLfloat(0.7f, 0.9f);
}

void OBJECT_CLOUD::initBuffer(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;
	//// 5.1. VAO 객체 생성 및 바인딩
	glGenVertexArrays(1, &vao);

	// 2 triangles for quad floor
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outvertex.size() * sizeof(glm::vec3), &objReader.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(m_ShaderProgram, "vPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outnormal.size() * sizeof(glm::vec3), &objReader.outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(m_ShaderProgram, "vNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);

	objColorLocation = glGetUniformLocation(m_ShaderProgram, "objectColor"); //--- object Color값 전달
}

void OBJECT_CLOUD::initTexture(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;
}

void OBJECT_CLOUD::Render()
{

}

void OBJECT_CLOUD::Render(unsigned int modelLocation)
{
	for (int i = 0; i < MAX_CLOUD_CREATE; i++) {
		putFactor(i, glm::mat4(1.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getFactor(i)));

		glUseProgram(m_ShaderProgram);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniform4f(objColorLocation, pData[i].fColor_r, pData[i].fColor_g, pData[i].fColor_b, pData[i].fColor_a);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, ObjectModel[pData[i].iObjectStatus]);

		glDisable(GL_BLEND);
	}
}

void OBJECT_CLOUD::Update(float fTimeElapsed)
{
	for (int i = 0; i < MAX_CLOUD_CREATE; i++) {
		pData[i].fObject_z += pData[i].ObjectSpeed * fTimeElapsed;
		if (pData[i].fObject_z >= 30.0f) {
			CoordiSet(i);
		}
	}
}

void OBJECT_CLOUD::putFactor(glm::mat4 inputFactor)
{

}

void OBJECT_CLOUD::putFactor(GLint index, glm::mat4 inputFactor)
{
	pData[index].Factor = inputFactor;
	pData[index].Factor = glm::translate(pData[index].Factor, glm::vec3(pData[index].fObject_x, pData[index].fObject_y, pData[index].fObject_z));
	//myFactor = scale(myFactor, glm::vec3(0.2f, 0.2f, 0.2f));
}

glm::mat4 OBJECT_CLOUD::getFactor()
{
	return pData[0].Factor;
}

glm::mat4 OBJECT_CLOUD::getFactor(GLint index)
{
	return pData[index].Factor;
}
