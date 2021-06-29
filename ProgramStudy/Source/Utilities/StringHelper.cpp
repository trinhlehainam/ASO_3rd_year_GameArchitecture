#include "StringHelper.h"

#include <fstream>
#include <sstream>

namespace StringHelper
{
	std::string LoadFileToStringBuffer(const std::string& fileName)
	{
		std::ifstream file(fileName);
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		return buffer.str();
	}
};
