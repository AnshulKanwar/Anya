#ifndef PARSER_H
#define PARSER_H

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace Parser {
    po::variables_map parse(int argc, const char** argv);
}

#endif