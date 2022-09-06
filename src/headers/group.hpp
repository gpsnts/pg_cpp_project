#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include <string>
#include <vector>

#include "pch/glad_pch.hpp"

#include "headers/face.hpp"

class Group
{
private:
	GLint VAO;
	std::string group_name, material;
	std::vector<Face> faces;
public:
};

#endif // __GROUP_HPP__