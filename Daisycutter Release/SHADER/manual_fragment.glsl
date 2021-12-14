// 메뉴를 띄우기 위한 셰이더
#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

uniform sampler2D outTexture;

void main()
{
	FragColor = texture(outTexture, TexCoord);
}