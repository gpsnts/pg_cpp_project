#ifndef __GL_UTILS_HPP__
#define __GL_UTILS_HPP__

#include <iostream>
#include <string>

#include "pch/glad_pch.hpp"
#include "pch/glfw_pch.hpp"

#include "stb_image.h"
#include <stb/stb_image.h>

class GlUtils
{
private:
	bool init_glfw();
	bool set_profile();

  GlUtils() {}
public:
	bool init();
	template<typename T> void static debug_print(T arg)
	{ 
		#ifdef DEBUG_MODE
			std::cout << "Debug: " << arg << std::endl;
		#else
			return;
		#endif // DEBUG_PRINT
	}

  static unsigned char* stbi_load_image(std::string const &file_loc, GLboolean alpha);
};

#endif // __GL_UTILS_HPP__
