#version 330
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 ModelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * viewTransform * ModelTransform * vec4(vPos, 1.0);

	FragPos = vec3(ModelTransform * vec4(vPos, 1.0));
	Normal = normalize(vec3(ModelTransform * vec4(vNormal, 0)));
	TexCoord = vTexCoord;
}