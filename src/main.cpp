#include "anya.h"
#include "parser.h"

#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;

int main(int argc, const char **argv)
{
    po::variables_map vm = Parser::parse(argc, argv);

    spdlog::info("Starting App");

    Anya app(vm["source-dir"].as<std::string>());
    app.listen(vm["port"].as<int>());
}