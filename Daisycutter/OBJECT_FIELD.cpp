#include "OBJECT_FIELD.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLfloat OBJECT_FIELD::data[6][2][2][3][3];
GLfloat OBJECT_FIELD::texture_data[6][2][3][2];

OBJECT_FIELD::OBJECT_FIELD()
{
	OnCreate();
}

OBJECT_FIELD::~OBJECT_FIELD()
{

}

void OBJECT_FIELD::OnCreate()
{
	GLfloat linear = 1024.0f;	// ������ü�� ����� ���� �� ���ϴ� ������ ������ �Է����ݴϴ�.

	GLfloat front_left_down_x = -linear, front_left_down_y = -linear, front_left_down_z = linear;		// ������ü�� ����� ���� �� �ּ� �����մϴ�.
	GLfloat front_left_top_x = -linear, front_left_top_y = linear, front_left_top_z = linear;
	GLfloat front_right_down_x = linear, front_right_down_y = -linear, front_right_down_z = linear;
	GLfloat front_right_top_x = linear, front_right_top_y = linear, front_right_top_z = linear;
	GLfloat back_left_down_x = -linear, back_left_down_y = -linear, back_left_down_z = -linear;
	GLfloat back_left_top_x = -linear, back_left_top_y = linear, back_left_top_z = -linear;
	GLfloat back_right_down_x = linear, back_right_down_y = -linear, back_right_down_z = -linear;
	GLfloat back_right_top_x = linear, back_right_top_y = linear, back_right_top_z = -linear;

	// ���� ��ǥ
	data[0][0][0][0][0] = front_left_down_x, data[0][0][0][0][1] = front_left_down_y, data[0][0][0][0][2] = front_left_down_z;
	data[0][0][0][1][0] = front_right_down_x, data[0][0][0][1][1] = front_right_down_y, data[0][0][0][1][2] = front_right_down_z;
	data[0][0][0][2][0] = front_left_top_x, data[0][0][0][2][1] = front_left_top_y, data[0][0][0][2][2] = front_left_top_z;

	data[0][0][1][0][0] = front_left_top_x, data[0][0][1][0][1] = front_left_top_y, data[0][0][1][0][2] = front_left_top_z;
	data[0][0][1][1][0] = front_right_down_x, data[0][0][1][1][1] = front_right_down_y, data[0][0][1][1][2] = front_right_down_z;
	data[0][0][1][2][0] = front_right_top_x, data[0][0][1][2][1] = front_right_top_y, data[0][0][1][2][2] = front_right_top_z;

	// ���� ���
	data[0][1][0][0][0] = 0.0f, data[0][1][0][0][1] = 0.0f, data[0][1][0][0][2] = -1.0f;
	data[0][1][0][1][0] = 0.0f, data[0][1][0][1][1] = 0.0f, data[0][1][0][1][2] = -1.0f;
	data[0][1][0][2][0] = 0.0f, data[0][1][0][2][1] = 0.0f, data[0][1][0][2][2] = -1.0f;

	data[0][1][1][0][0] = 0.0f, data[0][1][1][0][1] = 0.0f, data[0][1][1][0][2] = -1.0f;
	data[0][1][1][1][0] = 0.0f, data[0][1][1][1][1] = 0.0f, data[0][1][1][1][2] = -1.0f;
	data[0][1][1][2][0] = 0.0f, data[0][1][1][2][1] = 0.0f, data[0][1][1][2][2] = -1.0f;

	// ���� �ؽ�ó
	texture_data[0][0][0][0] = 0.0f, texture_data[0][0][0][1] = 0.0f;
	texture_data[0][0][1][0] = 1.0f, texture_data[0][0][1][1] = 0.0f;
	texture_data[0][0][2][0] = 0.0f, texture_data[0][0][2][1] = 1.0f;

	texture_data[0][1][0][0] = 0.0f, texture_data[0][1][0][1] = 1.0f;
	texture_data[0][1][1][0] = 1.0f, texture_data[0][1][1][1] = 0.0f;
	texture_data[0][1][2][0] = 1.0f, texture_data[0][1][2][1] = 1.0f;


	// ��� ��ǥ
	data[1][0][0][0][0] = front_right_top_x, data[1][0][0][0][1] = front_right_top_y, data[1][0][0][0][2] = front_right_top_z;
	data[1][0][0][1][0] = back_right_top_x, data[1][0][0][1][1] = back_right_top_y, data[1][0][0][1][2] = back_right_top_z;
	data[1][0][0][2][0] = front_left_top_x, data[1][0][0][2][1] = front_left_top_y, data[1][0][0][2][2] = front_left_top_z;

	data[1][0][1][0][0] = front_left_top_x, data[1][0][1][0][1] = front_left_top_y, data[1][0][1][0][2] = front_left_top_z;
	data[1][0][1][1][0] = back_right_top_x, data[1][0][1][1][1] = back_right_top_y, data[1][0][1][1][2] = back_right_top_z;
	data[1][0][1][2][0] = back_left_top_x, data[1][0][1][2][1] = back_left_top_y, data[1][0][1][2][2] = back_left_top_z;

	// ��� ���
	data[1][1][0][0][0] = 0.0f, data[1][1][0][0][1] = -1.0f, data[1][1][0][0][2] = 0.0f;
	data[1][1][0][1][0] = 0.0f, data[1][1][0][1][1] = -1.0f, data[1][1][0][1][2] = 0.0f;
	data[1][1][0][2][0] = 0.0f, data[1][1][0][2][1] = -1.0f, data[1][1][0][2][2] = 0.0f;

	data[1][1][1][0][0] = 0.0f, data[1][1][1][0][1] = -1.0f, data[1][1][1][0][2] = 0.0f;
	data[1][1][1][1][0] = 0.0f, data[1][1][1][1][1] = -1.0f, data[1][1][1][1][2] = 0.0f;
	data[1][1][1][2][0] = 0.0f, data[1][1][1][2][1] = -1.0f, data[1][1][1][2][2] = 0.0f;

	// ��� �ؽ�ó
	texture_data[1][0][0][0] = 1.0f, texture_data[1][0][0][1] = 0.0f;
	texture_data[1][0][1][0] = 1.0f, texture_data[1][0][1][1] = 1.0f;
	texture_data[1][0][2][0] = 0.0f, texture_data[1][0][2][1] = 0.0f;

	texture_data[1][1][0][0] = 0.0f, texture_data[1][1][0][1] = 0.0f;
	texture_data[1][1][1][0] = 1.0f, texture_data[1][1][1][1] = 1.0f;
	texture_data[1][1][2][0] = 0.0f, texture_data[1][1][2][1] = 1.0f;


	// ���� ��ǥ
	data[2][0][0][0][0] = back_left_top_x, data[2][0][0][0][1] = back_left_top_y, data[2][0][0][0][2] = back_left_top_z;
	data[2][0][0][1][0] = back_left_down_x, data[2][0][0][1][1] = back_left_down_y, data[2][0][0][1][2] = back_left_down_z;
	data[2][0][0][2][0] = front_left_down_x, data[2][0][0][2][1] = front_left_down_y, data[2][0][0][2][2] = front_left_down_z;

	data[2][0][1][0][0] = front_left_down_x, data[2][0][1][0][1] = front_left_down_y, data[2][0][1][0][2] = front_left_down_z;
	data[2][0][1][1][0] = front_left_top_x, data[2][0][1][1][1] = front_left_top_y, data[2][0][1][1][2] = front_left_top_z;
	data[2][0][1][2][0] = back_left_top_x, data[2][0][1][2][1] = back_left_top_y, data[2][0][1][2][2] = back_left_top_z;

	// ���� ���
	data[2][1][0][0][0] = 1.0f, data[2][1][0][0][1] = 0.0f, data[2][1][0][0][2] = 0.0f;
	data[2][1][0][1][0] = 1.0f, data[2][1][0][1][1] = 0.0f, data[2][1][0][1][2] = 0.0f;
	data[2][1][0][2][0] = 1.0f, data[2][1][0][2][1] = 0.0f, data[2][1][0][2][2] = 0.0f;

	data[2][1][1][0][0] = 1.0f, data[2][1][1][0][1] = 0.0f, data[2][1][1][0][2] = 0.0f;
	data[2][1][1][1][0] = 1.0f, data[2][1][1][1][1] = 0.0f, data[2][1][1][1][2] = 0.0f;
	data[2][1][1][2][0] = 1.0f, data[2][1][1][2][1] = 0.0f, data[2][1][1][2][2] = 0.0f;

	// ���� �ؽ�ó
	texture_data[2][0][0][0] = 0.0f, texture_data[2][0][0][1] = 1.0f;
	texture_data[2][0][1][0] = 0.0f, texture_data[2][0][1][1] = 0.0f;
	texture_data[2][0][2][0] = 1.0f, texture_data[2][0][2][1] = 0.0f;

	texture_data[2][1][0][0] = 1.0f, texture_data[2][1][0][1] = 0.0f;
	texture_data[2][1][1][0] = 1.0f, texture_data[2][1][1][1] = 1.0f;
	texture_data[2][1][2][0] = 0.0f, texture_data[2][1][2][1] = 1.0f;


	// �ĸ� ��ǥ
	data[3][0][0][0][0] = back_left_top_x, data[3][0][0][0][1] = back_left_top_y, data[3][0][0][0][2] = back_left_top_z;
	data[3][0][0][1][0] = back_left_down_x, data[3][0][0][1][1] = back_left_down_y, data[3][0][0][1][2] = back_left_down_z;
	data[3][0][0][2][0] = back_right_top_x, data[3][0][0][2][1] = back_right_top_y, data[3][0][0][2][2] = back_right_top_z;

	data[3][0][1][0][0] = back_right_top_x, data[3][0][1][0][1] = back_right_top_y, data[3][0][1][0][2] = back_right_top_z;
	data[3][0][1][1][0] = back_left_down_x, data[3][0][1][1][1] = back_left_down_y, data[3][0][1][1][2] = back_left_down_z;
	data[3][0][1][2][0] = back_right_down_x, data[3][0][1][2][1] = back_right_down_y, data[3][0][1][2][2] = back_right_down_z;

	// �ĸ� ���
	data[3][1][0][0][0] = 0.0f, data[3][1][0][0][1] = 0.0f, data[3][1][0][0][2] = 1.0f;
	data[3][1][0][1][0] = 0.0f, data[3][1][0][1][1] = 0.0f, data[3][1][0][1][2] = 1.0f;
	data[3][1][0][2][0] = 0.0f, data[3][1][0][2][1] = 0.0f, data[3][1][0][2][2] = 1.0f;

	data[3][1][1][0][0] = 0.0f, data[3][1][1][0][1] = 0.0f, data[3][1][1][0][2] = 1.0f;
	data[3][1][1][1][0] = 0.0f, data[3][1][1][1][1] = 0.0f, data[3][1][1][1][2] = 1.0f;
	data[3][1][1][2][0] = 0.0f, data[3][1][1][2][1] = 0.0f, data[3][1][1][2][2] = 1.0f;

	// �ĸ� �ؽ�ó
	texture_data[3][0][0][0] = 0.0f, texture_data[3][0][0][1] = 1.0f;
	texture_data[3][0][1][0] = 0.0f, texture_data[3][0][1][1] = 0.0f;
	texture_data[3][0][2][0] = 1.0f, texture_data[3][0][2][1] = 1.0f;

	texture_data[3][1][0][0] = 1.0f, texture_data[3][1][0][1] = 1.0f;
	texture_data[3][1][1][0] = 0.0f, texture_data[3][1][1][1] = 0.0f;
	texture_data[3][1][2][0] = 1.0f, texture_data[3][1][2][1] = 0.0f;


	// �ϴ� ��ǥ
	data[4][0][0][0][0] = back_right_down_x, data[4][0][0][0][1] = back_right_down_y, data[4][0][0][0][2] = back_right_down_z;
	data[4][0][0][1][0] = front_right_down_x, data[4][0][0][1][1] = front_right_down_y, data[4][0][0][1][2] = front_right_down_z;
	data[4][0][0][2][0] = front_left_down_x, data[4][0][0][2][1] = front_left_down_y, data[4][0][0][2][2] = front_left_down_z;

	data[4][0][1][0][0] = front_left_down_x, data[4][0][1][0][1] = front_left_down_y, data[4][0][1][0][2] = front_left_down_z;
	data[4][0][1][1][0] = back_left_down_x, data[4][0][1][1][1] = back_left_down_y, data[4][0][1][1][2] = back_left_down_z;
	data[4][0][1][2][0] = back_right_down_x, data[4][0][1][2][1] = back_right_down_y, data[4][0][1][2][2] = back_right_down_z;

	// �ϴ� ���
	data[4][1][0][0][0] = 0.0f, data[4][1][0][0][1] = 1.0f, data[4][1][0][0][2] = 0.0f;
	data[4][1][0][1][0] = 0.0f, data[4][1][0][1][1] = 1.0f, data[4][1][0][1][2] = 0.0f;
	data[4][1][0][2][0] = 0.0f, data[4][1][0][2][1] = 1.0f, data[4][1][0][2][2] = 0.0f;

	data[4][1][1][0][0] = 0.0f, data[4][1][1][0][1] = 1.0f, data[4][1][1][0][2] = 0.0f;
	data[4][1][1][1][0] = 0.0f, data[4][1][1][1][1] = 1.0f, data[4][1][1][1][2] = 0.0f;
	data[4][1][1][2][0] = 0.0f, data[4][1][1][2][1] = 1.0f, data[4][1][1][2][2] = 0.0f;

	// �ϴ� �ؽ�ó
	texture_data[4][0][0][0] = 0.0f, texture_data[4][0][0][1] = 1.0f;
	texture_data[4][0][1][0] = 0.0f, texture_data[4][0][1][1] = 0.0f;
	texture_data[4][0][2][0] = 1.0f, texture_data[4][0][2][1] = 0.0f;

	texture_data[4][1][0][0] = 1.0f, texture_data[4][1][0][1] = 0.0f;
	texture_data[4][1][1][0] = 1.0f, texture_data[4][1][1][1] = 1.0f;
	texture_data[4][1][2][0] = 0.0f, texture_data[4][1][2][1] = 1.0f;


	// ���� ��ǥ
	data[5][0][0][0][0] = back_right_down_x, data[5][0][0][0][1] = back_right_down_y, data[5][0][0][0][2] = back_right_down_z;
	data[5][0][0][1][0] = back_right_top_x, data[5][0][0][1][1] = back_right_top_y, data[5][0][0][1][2] = back_right_top_z;
	data[5][0][0][2][0] = front_right_down_x, data[5][0][0][2][1] = front_right_down_y, data[5][0][0][2][2] = front_right_down_z;

	data[5][0][1][0][0] = front_right_down_x, data[5][0][1][0][1] = front_right_down_y, data[5][0][1][0][2] = front_right_down_z;
	data[5][0][1][1][0] = back_right_top_x, data[5][0][1][1][1] = back_right_top_y, data[5][0][1][1][2] = back_right_top_z;
	data[5][0][1][2][0] = front_right_top_x, data[5][0][1][2][1] = front_right_top_y, data[5][0][1][2][2] = front_right_top_z;

	// ���� ���
	data[5][1][0][0][0] = -1.0f, data[5][1][0][0][1] = 0.0f, data[5][1][0][0][2] = 0.0f;
	data[5][1][0][1][0] = -1.0f, data[5][1][0][1][1] = 0.0f, data[5][1][0][1][2] = 0.0f;
	data[5][1][0][2][0] = -1.0f, data[5][1][0][2][1] = 0.0f, data[5][1][0][2][2] = 0.0f;

	data[5][1][1][0][0] = -1.0f, data[5][1][1][0][1] = 0.0f, data[5][1][1][0][2] = 0.0f;
	data[5][1][1][1][0] = -1.0f, data[5][1][1][1][1] = 0.0f, data[5][1][1][1][2] = 0.0f;
	data[5][1][1][2][0] = -1.0f, data[5][1][1][2][1] = 0.0f, data[5][1][1][2][2] = 0.0f;

	// ���� �ؽ�ó
	texture_data[5][0][0][0] = 1.0f, texture_data[5][0][0][1] = 0.0f;
	texture_data[5][0][1][0] = 1.0f, texture_data[5][0][1][1] = 1.0f;
	texture_data[5][0][2][0] = 0.0f, texture_data[5][0][2][1] = 0.0f;

	texture_data[5][1][0][0] = 0.0f, texture_data[5][1][0][1] = 0.0f;
	texture_data[5][1][1][0] = 1.0f, texture_data[5][1][1][1] = 1.0f;
	texture_data[5][1][2][0] = 0.0f, texture_data[5][1][2][1] = 1.0f;
}

void OBJECT_FIELD::initBuffer(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;

	glGenVertexArrays(6, vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glGenBuffers(3, vbo[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][1]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i][1], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][2]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), texture_data[i], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(2);
	}

	glUseProgram(m_ShaderProgram);
	objColorLocation = glGetUniformLocation(m_ShaderProgram, "objectColor"); //--- object Color�� ����
}

void OBJECT_FIELD::initTexture(GLint ShaderProgram)
{
	m_ShaderProgram = ShaderProgram;

	glGenTextures(6, texture); //--- �ؽ�ó ����
	for (int i = 0; i < 6; i++) {
		char Text[100];
		int widthImage, heightImage, numberOfChannel;
		stbi_set_flip_vertically_on_load(true);
		glBindTexture(GL_TEXTURE_2D, texture[i]); //--- �ؽ�ó ���ε�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		sprintf(Text, "GRAPHIC\\OBJECT\\FIELD\\FIELD%d.png", i);
		image[i] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- �ؽ�ó�� ����� ��Ʈ�� �̹��� �ε��ϱ�
		glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]); //---�ؽ�ó �̹��� ����

		stbi_image_free(image[i]);
	}

	glUseProgram(m_ShaderProgram);
	tLocation = glGetUniformLocation(m_ShaderProgram, "outTexture"); //--- outTexture ������ ���÷��� ��ġ�� ������
	glUniform1i(tLocation, 0);
}

void OBJECT_FIELD::Render()
{
	for (int i = 0; i < 6; i++) {
		glUseProgram(m_ShaderProgram);
		glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
		glBindVertexArray(vao[i]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void OBJECT_FIELD::Update(float fTimeElapsed)
{

}

void OBJECT_FIELD::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
}

glm::mat4 OBJECT_FIELD::getFactor()
{
	return myFactor;
}
