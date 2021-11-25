#version 330
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;

out vec3 FragPos;								// 프래그먼트 세이더에게 전달
out vec3 Normal;

uniform mat4 ModelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * viewTransform * ModelTransform * vec4(vPos, 1.0);
	FragPos = vec3(ModelTransform * vec4(vPos, 1.0));
	// Normal = mat3(transpose(inverse(ModelTransform))) * vNormal;
	Normal = normalize(vec3(ModelTransform * vec4(vNormal ,0)));
}