#pragma once

#include <string>

class HttpParser
{
public:
    static std::string getPath(const std::string& request);
};