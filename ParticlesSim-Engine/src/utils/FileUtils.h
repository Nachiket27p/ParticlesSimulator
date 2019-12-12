#pragma once

#include <string>
#include <fstream>

namespace particlesSimulator
{
	class FileUtils
	{
	public:
		static inline std::string read_file(const char* filePath)
		{
			FILE* file = fopen(filePath, "rt");

			fseek(file, 0, SEEK_END);
			unsigned long len = ftell(file);
			fseek(file, 0, SEEK_SET);

			char* data = (char*)calloc(len + (unsigned long)1, sizeof(char));

			if (!len) {
				return nullptr;
			}

			fread(data, 1, len, file);

			fclose(file);

			std::string result(data);

			free(data);

			return result;
		}
	};
	
}