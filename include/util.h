#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <vector>

template <typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);

std::stringstream read_file(const std::string &path);

#endif