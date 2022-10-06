#include "response.h"

#include <fmt/core.h>

#include <string>
#include <sstream>
#include <unordered_map>
// #include <format>

Response::Response(
    std::string http_version,
    int status_code,
    std::string reason_phrase,
    std::string message_body)
    : http_version(http_version),
      status_code(status_code),
      reason_phrase(reason_phrase),
      message_body(message_body)
{
    headers["Content-Length"] = std::to_string(message_body.length());
};

std::string Response::response_str()
{
    std::string status_line = fmt::format("{} {} {} \r\n", http_version, status_code, reason_phrase);

    std::string header_str = "";
    for (auto &it : headers)
    {
        header_str += fmt::format("{}: {}\r\n", it.first, it.second);
    }

    std::string res_str = fmt::format("{}{}\r\n{}", status_line, header_str, message_body);
    return res_str;
}

void Response::set_header(const std::string &key, const std::string &value)
{
    this->headers[key] = value;
}

const std::string &Response::get_header(const std::string &key)
{
    return this->headers.at(key);
}

std::string get_content_type(const std::string &extension)
{
    if (content_type_map.find(extension) == content_type_map.end())
    {
        return "application/octet-stream";
    }
    else
    {
        return content_type_map.at(extension);
    }
}