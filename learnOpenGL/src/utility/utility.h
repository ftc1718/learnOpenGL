#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <stb_image.h>

unsigned int loadTexture(const char* path);
unsigned int loadCubemap(const std::vector<std::string>& faces);
