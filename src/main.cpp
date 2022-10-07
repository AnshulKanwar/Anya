#include "anya.h"
#include "parser.h"

#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>

#include <unordered_map>

namespace po = boost::program_options;

int main(int argc, const char **argv)
{
    po::variables_map vm = Parser::parse(argc, argv);

    std::unordered_map<std::string, spdlog::level::level_enum> spdlog_level_map = {
        {"err", spdlog::level::err},
        {"warn", spdlog::level::warn},
        {"debug", spdlog::level::debug},
        {"info", spdlog::level::info},
    };
    spdlog::set_level(spdlog_level_map.at(vm["log"].as<std::string>()));

    spdlog::info("Starting App");

    Anya app(vm["source-dir"].as<std::string>());
    app.listen(vm["port"].as<int>());
}