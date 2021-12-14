#include "OBJECT_CLOUD.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

OBJECT_CLOUD::OBJECT_CLOUD()
{
	OnCreate();
}

OBJECT_CLOUD::~OBJECT_CLOUD()
{

}

void OBJECT_CLOUD::OnCreate()
{
	char Text[100];
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> status(1, 2);
	std::uniform_real_distribution<float> coordinate(-3.0f, 3.0f);
	std::uniform_real_distribution<float> zcoordinate(-150.0f, 0.0f);
	std::uniform_real_distribution<float> speed(3.0f, 7.0f);
	CloudStatus = status(dre);

	sprintf(Text, "GRAPHIC\\OBJECT\\CLOUD\\CLOUD%d.obj", CloudStatus);
	ObjectModel = objReader.loadObj_normalize_center(Text);
	object_x = coordinate(dre), object_y = coordinate(dre), object_z = zcoordinate(dre);
	ObjectSpeed = speed(dre);
}

void OBJECT_CLOUD::CoordiSet()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> coordinate(-3.0f, 3.0f);
	std::uniform_real_distribution<float> speed(3.0f, 7.0f);

	object_x = coordinate(dre), object_y = coordinate(dre), object_z = -150.0;
	ObjectSpeed = speed(dre);
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

	glGenBuffers(1, &vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outuv.size() * sizeof(glm::vec2), &objReader.outuv[0], GL_STATIC_DRAW);
	GLint tAttribute = glGetAttribLocation(m_ShaderProgram, "vTexCoord");
	glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(tAttribute);

	objColorLocation = glGetUniformLocation(m_ShaderProgram, "objectColor"); //--- object Color값 전달
}

void OBJECT_CLOUD::initTexture(GLint ShaderProgram)
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
	sprintf(Text, "GRAPHIC\\OBJECT\\CLOUD\\CLOUD_TEXTURE.png");
	image = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); //---텍스처 이미지 정의

	stbi_image_free(image);

	glUseProgram(m_ShaderProgram);
	tLocation = glGetUniformLocation(m_ShaderProgram, "outTexture"); //--- outTexture 유니폼 샘플러의 위치를 가져옴
	glUniform1i(tLocation, 0);
}

void OBJECT_CLOUD::Render()
{
	glUseProgram(m_ShaderProgram);
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, ObjectModel);
}

void OBJECT_CLOUD::Update(float fTimeElapsed)
{
	object_z += ObjectSpeed * fTimeElapsed;
	if (object_z >= 10.0f) {
		CoordiSet();
	}
}

void OBJECT_CLOUD::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(object_x, object_y, object_z));
	//myFactor = scale(myFactor, glm::vec3(0.2f, 0.2f, 0.2f));
}

glm::mat4 OBJECT_CLOUD::getFactor()
{
	return myFactor;
}
