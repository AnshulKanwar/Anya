#include "request.h"
#include "util.h"

#include <spdlog/spdlog.h>

#include <string>
#include <sstream>
#include <unordered_map>

Request::Request(std::string &raw_request)
{
    parse_request(raw_request);
}

void Request::parse_request(const std::string &raw_request)
{
    std::istringstream iss(raw_request);
    std::string line;

    // FIXME: Add error handling
    std::getline(iss, line);
    parse_request_line(line);

    while (std::getline(iss, line) && line.compare("\r") != 0)
    {
        parse_header(line);
    }

    std::getline(iss, line);
    parse_body(line);
}

void Request::parse_request_line(const std::string &request_line)
{
    std::vector<std::string> tokens = split(request_line, ' ');

    // FIXME: Add error handling
    parse_method(tokens[0]);
    parse_uri(tokens[1]);
    parse_http_version(tokens[2]);
}

void Request::parse_method(const std::string &method)
{
    auto it = table.find(method);
    if (it != table.end())
    {
        this->method = it->second;
    }
    else
    {
        spdlog::error("Unknown request method {}", method);
        exit(EXIT_FAILURE);
    }
}

void Request::parse_uri(const std::string &uri)
{
    this->uri = uri;
}

void Request::parse_http_version(const std::string &http_version)
{
    this->http_version = http_version;
}

void Request::parse_header(const std::string &header)
{
    std::vector<std::string> key_value = split(header, ':');
    this->headers[key_value[0]] = key_value[1].substr(1);
}

void Request::parse_body(const std::string &body)
{
    this->body = body;
}