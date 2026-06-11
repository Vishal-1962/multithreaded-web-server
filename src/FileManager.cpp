#include "../include/FileManager.h"

#include <fstream>
#include <sstream>

std::string FileManager::readFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return "";
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}