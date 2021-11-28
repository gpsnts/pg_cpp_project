#ifndef __GL_UTILS_HPP__
#define __GL_UTILS_HPP__

#include <iostream>

#include "pch/glad_pch.hpp"
#include "pch/glfw_pch.hpp"

class GlUtils
{
private:
	bool init_glfw();
	bool set_profile();	
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
};

#endif // __GL_UTILS_HPP__
