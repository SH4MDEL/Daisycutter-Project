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
		pData[i].DieStateTimer = 0.0f;
		pData[i].iObjectStatus = NullState;
		pData[i].Factor = glm::mat4(1.0f);
		pData[i].particle = NULL;
	}
	iNowIndex = 0;
}

void OBJECT_ENEMY::EnemyCreate(GLint Location)
{
	GLfloat weight = 1.0f;
	for (int i = 0; i < MAX_ENEMY_CREATE; i++) {
		if (pData[i].iObjectStatus == NullState) {
			pData[i].iObjectStatus = ActiveState;
			if (Location == 1) {
				pData[i].fObject_x = -1.0f;
				pData[i].fObject_y = 1.0f;
				pData[i].fObject_z = -150.0f;
			}
			else if (Location == 2) {
				pData[i].fObject_x = 1.0f;
				pData[i].fObject_y = 1.0f;
				pData[i].fObject_z = -150.0f;
			}
			else if (Location == 3) {
				pData[i].fObject_x = -1.0f;
				pData[i].fObject_y = -1.0f;
				pData[i].fObject_z = -150.0f;
			}
			else if (Location == 4) {
				pData[i].fObject_x = 1.0f;
				pData[i].fObject_y = -1.0f;
				pData[i].fObject_z = -150.0f;
			}
			else if (Location == 5) {
				pData[i].fObject_x = 0.0f;
				pData[i].fObject_y = 0.0f;
				pData[i].fObject_z = -150.0f;
			}
			else if (Location == 6) {
				pData[i].fObject_x = 0.0f;
				pData[i].fObject_y = 2.0f;
				pData[i].fObject_z = -150.0f;
			}
			else if (Location == 7) {
				pData[i].fObject_x = -2.0f;
				pData[i].fObject_y = 0.0f;
				pData[i].fObject_z = -150.0f;
			}
			else if (Location == 8) {
				pData[i].fObject_x = 2.0f;
				pData[i].fObject_y = 0.0f;
				pData[i].fObject_z = -150.0f;
			}
			else if (Location == 9) {
				pData[i].fObject_x = 0.0f;
				pData[i].fObject_y = -2.0f;
				pData[i].fObject_z = -150.0f;
			}
			break;
		}
	}
}

void OBJECT_ENEMY::initBuffer(GLint ShaderProgram)
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

	glGenBuffers(1, &vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outuv.size() * sizeof(glm::vec2), &objReader.outuv[0], GL_STATIC_DRAW);
	GLint tAttribute = glGetAttribLocation(m_ShaderProgram, "vTexCoord");
	glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(tAttribute);

	lightPosLocation[0] = glGetUniformLocation(ShaderProgram, "lightPos"); //--- lightPos 값 전달
	lightColorLocation[0] = glGetUniformLocation(ShaderProgram, "lightColor"); //--- lightColor 값 전달
	objColorLocation = glGetUniformLocation(m_ShaderProgram, "objectColor"); //--- object Color값 전달
}

void OBJECT_ENEMY::initTexture(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;

	glGenTextures(1, &texture); //--- 텍스처 생성
	char Text[100];
	int widthImage, heightImage, numberOfChannel;
	stbi_set_flip_vertically_on_load(true);
	glBindTexture(GL_TEXTURE_2D, texture); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\OBJECT\\ENEMY\\ENEMY_TEXTURE.png");
	image = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); //---텍스처 이미지 정의

	stbi_image_free(image);

	glUseProgram(m_ShaderProgram);
	tLocation = glGetUniformLocation(m_ShaderProgram, "outTexture"); //--- outTexture 유니폼 샘플러의 위치를 가져옴
	glUniform1i(tLocation, 0);
}

void OBJECT_ENEMY::initSubShader(GLint ShaderProgram)
{
	lightPosLocation[1] = glGetUniformLocation(ShaderProgram, "lightPos"); //--- lightPos 값 전달
	lightColorLocation[1] = glGetUniformLocation(ShaderProgram, "lightColor"); //--- lightColor 값 전달
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
			pData[i].Factor = glm::scale(pData[i].Factor, glm::vec3(0.2, 0.2, 1.0));
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

void OBJECT_ENEMY::ParticleRender(unsigned int modelLocation)
{
	for (int i = 0; i < MAX_ENEMY_CREATE; i++) {
		if (pData[i].iObjectStatus == DieState) {
			for (int j = 0; j < MAX_PARTICLE_CREATE; j++) {
				pData[i].particle[j].Render(modelLocation);
			}
		}
	}
}

void OBJECT_ENEMY::putParticleShader(GLint ShaderProgram)
{
	m_ParticleShaderProgram = ShaderProgram;
}

void OBJECT_ENEMY::Update(float fTimeElapsed)
{
	for (int i = 0; i < MAX_ENEMY_CREATE; i++) {
		if (pData[i].iObjectStatus == ActiveState) {
			if (pData[i].fObject_z >= 10.0f) {
				pData[i].iObjectStatus = InvincibleState;
			}
			pData[i].fObject_z += (GLfloat)((m_dBPM / SECOND_PER_MINITE) * 150.0f / 4.0f * fTimeElapsed);
		}
		else if (pData[i].iObjectStatus == InvincibleState) {
			pData[i].fObject_z += (GLfloat)((m_dBPM / SECOND_PER_MINITE) * 150.0f / 4.0f * fTimeElapsed);
		}
		else if (pData[i].iObjectStatus == DieState) {
			pData[i].DieStateTimer += fTimeElapsed;
			for (int j = 0; j < MAX_PARTICLE_CREATE; j++) {
				pData[i].particle[j].Update(fTimeElapsed);
			}
			if (pData[i].DieStateTimer >= 3.0f) {
				pData[i].DieStateTimer = 0.0f;
				EnemyRemove(i);
			}
		}
	}
}

bool OBJECT_ENEMY::EnemyAttacked()
{
	GLfloat MaxZ = -10.0f;
	GLint index = -1;
	for (int i = 0; i < MAX_ENEMY_CREATE; i++) {
		if (pData[i].iObjectStatus == ActiveState && pData[i].fObject_z > MaxZ) {
			MaxZ = pData[i].fObject_z;
			index = i;
		}
	}
	if (index == -1) {
		return false;
	}
	else {
		EnemyDie(index);
		return true;
	}
}

void OBJECT_ENEMY::EnemyDie(GLint index)
{
	pData[index].particle = new OBJECT_PARTICLE[MAX_PARTICLE_CREATE];
	for (int i = 0; i < MAX_PARTICLE_CREATE; i++) {
		pData[index].particle[i].PutData(pData[index].fObject_x, pData[index].fObject_y, pData[index].fObject_z);
		pData[index].particle[i].initBuffer(m_ParticleShaderProgram);
		pData[index].particle[i].initTexture(m_ParticleShaderProgram);
	}
	pData[index].fObject_z = -150.0f;
	pData[index].iObjectStatus = DieState;
}

void OBJECT_ENEMY::EnemyRemove(GLint index)
{
	if (pData[index].particle != NULL) {
		delete[] pData[index].particle;
		pData[index].particle = NULL;
	}
	pData[index].fObject_z = -150.0f;
	pData[index].iObjectStatus = NullState;
}

void OBJECT_ENEMY::putFactor(glm::mat4 inputFactor)
{

}

glm::mat4 OBJECT_ENEMY::getFactor()
{
	return glm::mat4(1.0f);
}

GLfloat OBJECT_ENEMY::getOz(GLint index)
{
	return pData[index].fObject_z;
}