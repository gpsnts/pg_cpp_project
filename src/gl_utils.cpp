#include "headers/gl_utils.hpp"
#include "stb_image.h"

unsigned char* GlUtils::stbi_load_image(std::string const &file_loc, GLboolean alpha)
{
  int width, height, channels;
  unsigned char* image;

  GlUtils::debug_print("Loading texture: " + file_loc);
	
	if (alpha) image = stbi_load(file_loc.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	else image = stbi_load(file_loc.c_str(), &width, &height, &channels,  STBI_rgb);

	if (!image) fprintf(stderr, "%s %s\n", "Failed to Load Texture", file_loc.c_str());

  stbi_image_free(image);
  return image;
}