#pragma once
#include "Shader.h"
class Material
{
public:
	Shader* shader;
	vec3 ambient;
	uint diffuse;
	uint specqular; 
	float shininess;
	Material(Shader* _shader, vec3 _ambient, uint _diffuse, uint _specqular, float _shininess)
	{
		shader = _shader, ambient = _ambient, diffuse = _diffuse, specqular = _specqular, shininess = _shininess;
	}
};