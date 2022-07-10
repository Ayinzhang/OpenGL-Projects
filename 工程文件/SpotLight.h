#pragma once
#include "opengl.h"
class SpotLight
{
public:
	vec3 position, angles, color, direction = { 0,0,1 }; float cosPhiInner = 0.9, cosPhiOutter = 0.85;
	SpotLight(vec3 _position, vec3 _angles, vec3 _color = { 1,1,1 })
	{
		position = _position, angles = _angles, color = _color;
	}
	void UpdateDirection()
	{
		direction = { 0,0,1 };
		direction = rotateZ(direction, angles.z);
		direction = rotateX(direction, angles.x);
		direction = rotateY(direction, angles.y);
		direction = -direction;
	}
};