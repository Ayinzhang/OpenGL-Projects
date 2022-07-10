#pragma once
#include "opengl.h"
class PointLight
{
public:
	vec3 position, color, attenuation = { 1.0,0.14,0.07 };
	PointLight(vec3 _position, vec3 _color = { 1,1,1 })
	{
		position = _position, color = _color;
	}
};