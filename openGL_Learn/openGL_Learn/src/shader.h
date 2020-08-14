#pragma once

#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragPath);

	void use();

	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setBool(const std::string& name, bool value) const;
	void setFloat4(const std::string& name, float value0, float value1, float value2, float value3) const;
};