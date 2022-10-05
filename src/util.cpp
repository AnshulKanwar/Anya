#include "util.h"

#include <iostream>
#include <fstream>
#include <sstream>

template <typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim))
    {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::stringstream read_file(const std::string &path)
{
    std::ifstream ifs(path);
    std::stringstream buffer;

    if (!ifs.is_open()) {
        std::cerr << "Could not open the file - '" << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    buffer << ifs.rdbuf();

    return buffer;
}