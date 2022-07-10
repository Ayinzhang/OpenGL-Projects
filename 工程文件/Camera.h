#pragma once
#include "opengl.h"
class Camera
{
public:
	vec3 position, forward, right, up, worldUp; float yaw, pitch;
	Camera(vec3 _position, vec3 target, vec3 worldup)
	{
		position = _position; worldUp = worldup;
		forward = normalize(target - position);
		right = normalize(cross(forward, worldUp));
		up = -normalize(cross(forward, right));
	}
	Camera(vec3 _position, float pitch, float yaw, vec3 worldup)
	{
		position = _position; worldUp = worldup; pitch = pitch; yaw = yaw;
		forward = vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
		right = normalize(cross(forward, worldUp));
		up = -normalize(cross(forward, right));
	}
	mat4 GetViewMatrix()
	{
		return lookAt(position, forward + position, worldUp);
	}
	void ProcessMouseMovement(float daltax, float daltay)
	{
		yaw -= 0.01 * daltax; pitch -= 0.01 * daltay;
		UpdateCameraVectors();
	}
	void UpdateCameraVectors()
	{
		forward = vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
		right = normalize(cross(forward, worldUp));
		up = -normalize(cross(forward, right));
	}
};