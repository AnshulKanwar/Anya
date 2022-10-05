#include "util.h"

#include <spdlog/spdlog.h>

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

    if (!ifs.is_open())
    {
        throw std::runtime_error("Could not open file - '" + path + "'");
        std::ifstream error404("./404.html");
        buffer << error404.rdbuf();
    }
    else
    {
        buffer << ifs.rdbuf();
    }

    return buffer;
}

std::string get_extension(const std::string &filename)
{
    return filename.substr(filename.find_last_of("."));
}