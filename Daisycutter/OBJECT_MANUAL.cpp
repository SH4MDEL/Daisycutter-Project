#include "OBJECT_MANUAL.h"
#include "stb_image.h"

GLfloat OBJECT_MANUAL::data[2][2][3][3];
GLfloat OBJECT_MANUAL::texture_data[2][3][2];

OBJECT_MANUAL::OBJECT_MANUAL()
{
	OnCreate();
}

OBJECT_MANUAL::~OBJECT_MANUAL()
{

}

void OBJECT_MANUAL::OnCreate()
{
	GLfloat linear = 50.0f;	// 정육면체를 만들고 싶을 때 원하는 길이의 절반을 입력해줍니다.

	GLfloat front_left_down_x = -linear, front_left_down_y = -linear, front_left_down_z = linear;		// 정육면체를 만들고 싶을 때 주석 해제합니다.
	GLfloat front_left_top_x = -linear, front_left_top_y = linear, front_left_top_z = linear;
	GLfloat front_right_down_x = linear, front_right_down_y = -linear, front_right_down_z = linear;
	GLfloat front_right_top_x = linear, front_right_top_y = linear, front_right_top_z = linear;
	GLfloat back_left_down_x = -linear, back_left_down_y = -linear, back_left_down_z = -linear;
	GLfloat back_left_top_x = -linear, back_left_top_y = linear, back_left_top_z = -linear;
	GLfloat back_right_down_x = linear, back_right_down_y = -linear, back_right_down_z = -linear;
	GLfloat back_right_top_x = linear, back_right_top_y = linear, back_right_top_z = -linear;

	data[0][0][0][0] = back_left_top_x, data[0][0][0][1] = back_left_top_y, data[0][0][0][2] = back_left_top_z;
	data[0][0][1][0] = back_left_down_x, data[0][0][1][1] = back_left_down_y, data[0][0][1][2] = back_left_down_z;
	data[0][0][2][0] = back_right_top_x, data[0][0][2][1] = back_right_top_y, data[0][0][2][2] = back_right_top_z;

	data[0][1][0][0] = back_right_top_x, data[0][1][0][1] = back_right_top_y, data[0][1][0][2] = back_right_top_z;
	data[0][1][1][0] = back_left_down_x, data[0][1][1][1] = back_left_down_y, data[0][1][1][2] = back_left_down_z;
	data[0][1][2][0] = back_right_down_x, data[0][1][2][1] = back_right_down_y, data[0][1][2][2] = back_right_down_z;

	data[1][0][0][0] = 0.0f, data[1][0][0][1] = 0.0f, data[1][0][0][2] = 1.0f;
	data[1][0][1][0] = 0.0f, data[1][0][1][1] = 0.0f, data[1][0][1][2] = 1.0f;
	data[1][0][2][0] = 0.0f, data[1][0][2][1] = 0.0f, data[1][0][2][2] = 1.0f;

	data[1][1][0][0] = 0.0f, data[1][1][0][1] = 0.0f, data[1][1][0][2] = 1.0f;
	data[1][1][1][0] = 0.0f, data[1][1][1][1] = 0.0f, data[1][1][1][2] = 1.0f;
	data[1][1][2][0] = 0.0f, data[1][1][2][1] = 0.0f, data[1][1][2][2] = 1.0f;

	texture_data[0][0][0] = 0.0f, texture_data[0][0][1] = 1.0f;
	texture_data[0][1][0] = 0.0f, texture_data[0][1][1] = 0.0f;
	texture_data[0][2][0] = 1.0f, texture_data[0][2][1] = 1.0f;

	texture_data[1][0][0] = 1.0f, texture_data[1][0][1] = 1.0f;
	texture_data[1][1][0] = 0.0f, texture_data[1][1][1] = 0.0f;
	texture_data[1][2][0] = 1.0f, texture_data[1][2][1] = 0.0f;
}

void OBJECT_MANUAL::initBuffer(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(3, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[1], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), texture_data, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(2);

	glUseProgram(m_ShaderProgram);
	objColorLocation = glGetUniformLocation(m_ShaderProgram, "objectColor"); //--- object Color값 전달
}

void OBJECT_MANUAL::initTexture(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;

	glGenTextures(Count, texture); //--- 텍스처 생성
	char Text[100];
	int widthImage, heightImage, numberOfChannel;
	stbi_set_flip_vertically_on_load(true);

	glBindTexture(GL_TEXTURE_2D, texture[MainTitle]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\UI\\MAINTITLE.png");
	image[MainTitle] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[MainTitle]); //---텍스처 이미지 정의
	stbi_image_free(image[MainTitle]);

	glBindTexture(GL_TEXTURE_2D, texture[MusicSelect]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\UI\\MUSICSELECT.png");
	image[MusicSelect] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[MusicSelect]); //---텍스처 이미지 정의
	stbi_image_free(image[MusicSelect]);

	glBindTexture(GL_TEXTURE_2D, texture[OPERATION_START]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\UI\\OPERATION_START.png");
	image[OPERATION_START] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[OPERATION_START]); //---텍스처 이미지 정의
	stbi_image_free(image[OPERATION_START]);

	glBindTexture(GL_TEXTURE_2D, texture[NUMBER1]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\UI\\NUMBER_1.png");
	image[NUMBER1] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[NUMBER1]); //---텍스처 이미지 정의
	stbi_image_free(image[NUMBER1]);

	glBindTexture(GL_TEXTURE_2D, texture[NUMBER2]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\UI\\NUMBER_2.png");
	image[NUMBER2] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[NUMBER2]); //---텍스처 이미지 정의
	stbi_image_free(image[NUMBER2]);

	glBindTexture(GL_TEXTURE_2D, texture[NUMBER3]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\UI\\NUMBER_3.png");
	image[NUMBER3] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[NUMBER3]); //---텍스처 이미지 정의
	stbi_image_free(image[NUMBER3]);

	glBindTexture(GL_TEXTURE_2D, texture[HP_BAR]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sprintf(Text, "GRAPHIC\\UI\\HP_BAR.png");
	image[HP_BAR] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[HP_BAR]); //---텍스처 이미지 정의
	stbi_image_free(image[HP_BAR]);


	
	glUseProgram(m_ShaderProgram);
	tLocation = glGetUniformLocation(m_ShaderProgram, "outTexture"); //--- outTexture 유니폼 샘플러의 위치를 가져옴
	glUniform1i(tLocation, 0);
}

void OBJECT_MANUAL::Render()
{
	glUseProgram(m_ShaderProgram);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_BLEND);
}

void OBJECT_MANUAL::Render(GLint type)
{
	glUseProgram(m_ShaderProgram);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[type]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_BLEND);
}

void OBJECT_MANUAL::Update(float fTimeElapsed)
{

}

void OBJECT_MANUAL::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(0.0f, 0.0f, 10.0f));
}

glm::mat4 OBJECT_MANUAL::getFactor()
{
	return myFactor;
}
