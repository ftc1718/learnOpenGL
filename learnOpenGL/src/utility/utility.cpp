#include "utility.h"

unsigned int loadTexture(const char* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, channel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &channel, 0);
	if (data)
	{
		GLenum format;
		if (channel == 1)
		{
			format = GL_RED;
		}
		else if (channel == 3)
		{
			format = GL_RGB;
		}
		else if (channel == 4)
		{
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture at path: " << path << std::endl;
	}

	stbi_image_free(data);

	return textureID;
}