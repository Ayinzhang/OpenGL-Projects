#pragma once
#include "opengl.h"
class Shader
{
public:
	string vertexString, fragmentString;
	const char* vertexSource; const char* fragmentSource;
	uint ID, vertex, fragment;
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		ifstream vertexFile, fragmentFile;
		vertexFile.open(vertexPath), fragmentFile.open(fragmentPath);
		stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf(), fragmentStream << fragmentFile.rdbuf();
		vertexString = vertexStream.str(), fragmentString = fragmentStream.str();
		vertexSource = vertexString.c_str(); fragmentSource = fragmentString.c_str();
		glewExperimental = GL_TRUE; glewInit();
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		ID = glCreateProgram();
		glAttachShader(ID, vertex), glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glDeleteShader(vertex), glDeleteShader(fragment);
	}
	void use() { glUseProgram(ID); }
};