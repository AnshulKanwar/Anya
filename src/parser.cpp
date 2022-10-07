#include "parser.h"

#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;

po::variables_map Parser::parse(int argc, const char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "produce help message")
    ("port,p", po::value<int>()->default_value(3000), "set port to run on")
    ("log", po::value<std::string>()->default_value("info"), "set logging level (debug, info, warn, err)")
    ("source-dir", po::value<std::string>()->default_value("."), "set the source directory");

    po::positional_options_description p;
    p.add("source-dir", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        exit(0);
    }

    return vm;
}