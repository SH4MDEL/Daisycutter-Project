#include "OBJECT_ENEMY.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

objRead OBJECT_ENEMY::objReader;
GLint OBJECT_ENEMY::ObjectMedel = objReader.loadObj_normalize_center("GRAPHIC\\OBJECT\\ENEMY\\ENEMY.obj");

OBJECT_ENEMY::OBJECT_ENEMY()
{
	OnCreate();
}

OBJECT_ENEMY::OBJECT_ENEMY(GLdouble BPM)
{
	m_dBPM = BPM;
	OnCreate();
}

OBJECT_ENEMY::~OBJECT_ENEMY()
{
	delete[] pData;
}

void OBJECT_ENEMY::OnCreate()
{
	pData = new EnemyData[MAX_ENEMY_CREATE];
	for (int i = 0; i < MAX_ENEMY_CREATE; i++) {
		pData[i].fObject_x = 0.0f;
		pData[i].fObject_y = 0.0f;
		pData[i].fObject_z = 0.0f;
		pData[i].iObjectStatus = NullState;
		pData[i].Factor = glm::mat4(1.0f);
	}
	iStartIndex = 0;
	iEndIndex = 0;
	iNowIndex = 0;
}

void OBJECT_ENEMY::EnemyCreate(GLint Location)
{
	GLfloat weight = 2.5f;
	pData[iNowIndex].iObjectStatus = ActiveState;
	if (Location == 1) {
		pData[iNowIndex].fObject_x = -weight;
		pData[iNowIndex].fObject_y = weight;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	else if (Location == 2) {
		pData[iNowIndex].fObject_x = weight;
		pData[iNowIndex].fObject_y = weight;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	else if (Location == 3) {
		pData[iNowIndex].fObject_x = -weight;
		pData[iNowIndex].fObject_y = -weight;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	else if (Location == 4) {
		pData[iNowIndex].fObject_x = weight;
		pData[iNowIndex].fObject_y = -weight;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	else if (Location == 5) {
		pData[iNowIndex].fObject_x = 0.0f;
		pData[iNowIndex].fObject_y = 0.0f;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	else if (Location == 6) {
		pData[iNowIndex].fObject_x = 0.0f;
		pData[iNowIndex].fObject_y = 2.0f * weight;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	else if (Location == 7) {
		pData[iNowIndex].fObject_x = -2.0f * weight;
		pData[iNowIndex].fObject_y = 0.0f;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	else if (Location == 8) {
		pData[iNowIndex].fObject_x = 2.0f * weight;
		pData[iNowIndex].fObject_y = 0.0f;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	else if (Location == 9) {
		pData[iNowIndex].fObject_x = 0.0f;
		pData[iNowIndex].fObject_y = -2.0f * weight;
		pData[iNowIndex].fObject_z = -100.0f;
	}
	if (iNowIndex == MAX_ENEMY_CREATE - 1) {
		iNowIndex = 0;
	}
	else {
		iNowIndex++;
	}
	if (iEndIndex == MAX_ENEMY_CREATE - 1) {
		iEndIndex = 0;
	}
	else {
		iEndIndex++;
	}
}

void OBJECT_ENEMY::initBuffer(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;
	//// 5.1. VAO ��ü ���� �� ���ε�
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

	glGenBuffers(1, &vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outuv.size() * sizeof(glm::vec2), &objReader.outuv[0], GL_STATIC_DRAW);
	GLint tAttribute = glGetAttribLocation(m_ShaderProgram, "vTexCoord");
	glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(tAttribute);

	objColorLocation = glGetUniformLocation(m_ShaderProgram, "objectColor"); //--- object Color�� ����
}

void OBJECT_ENEMY::initTexture(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;

	glGenTextures(1, &texture); //--- �ؽ�ó ����
	char Text[100];
	int widthImage, heightImage, numberOfChannel;
	stbi_set_flip_vertically_on_load(true);
	glBindTexture(GL_TEXTURE_2D, texture); //--- �ؽ�ó ���ε�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\OBJECT\\ENEMY\\ENEMY_TEXTURE.png");
	image = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- �ؽ�ó�� ����� ��Ʈ�� �̹��� �ε��ϱ�
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); //---�ؽ�ó �̹��� ����

	stbi_image_free(image);

	glUseProgram(m_ShaderProgram);
	tLocation = glGetUniformLocation(m_ShaderProgram, "outTexture"); //--- outTexture ������ ���÷��� ��ġ�� ������
	glUniform1i(tLocation, 0);
}

void OBJECT_ENEMY::Render()
{
	glUseProgram(m_ShaderProgram);
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, ObjectMedel);
}

void OBJECT_ENEMY::Render(unsigned int modelLocation)
{
	for (int i = 0; i < MAX_ENEMY_CREATE; i++) {
		if (pData[i].iObjectStatus == ActiveState || pData[i].iObjectStatus == InvincibleState) {
			pData[i].Factor = glm::mat4(1.0f);
			pData[i].Factor = glm::translate(pData[i].Factor, glm::vec3(pData[i].fObject_x, pData[i].fObject_y, pData[i].fObject_z));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(pData[i].Factor));
			glUseProgram(m_ShaderProgram);
			glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
			glBindVertexArray(vao);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glDrawArrays(GL_TRIANGLES, 0, ObjectMedel);
		}
	}
}

void OBJECT_ENEMY::Update(float fTimeElapsed)
{
	for (int i = 0; i < MAX_ENEMY_CREATE; i++) {
		if (pData[i].iObjectStatus == ActiveState) {
			if (pData[i].fObject_z >= -10.0f) {
				pData[i].iObjectStatus = InvincibleState;
				continue;
			}
			pData[i].fObject_z += (GLfloat)m_dBPM / SECOND_PER_MINITE * 5.0f * 4.0f * fTimeElapsed;
		}
	}
}

void OBJECT_ENEMY::putFactor(glm::mat4 inputFactor)
{

}

glm::mat4 OBJECT_ENEMY::getFactor()
{
	return glm::mat4(1.0f);
}