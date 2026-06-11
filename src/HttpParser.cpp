#include "../include/HttpParser.h"

#include <sstream>

std::string HttpParser::getPath(const std::string& request)
{
    std::istringstream stream(request);

    std::string method;
    std::string path;

    stream >> method >> path;

    return path;
}