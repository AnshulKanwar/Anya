#include "response.h"

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
    // std::string fmt_str = "{} {} {} \r\n\r\n {}";
    // std::string response_str = std::format(fmt_str, this->http_version, this->status_code, this->reason_phrase, this->message_body);

    std::ostringstream response_ss;

    // status_line
    response_ss << http_version << " " << status_code << " " << reason_phrase << " "
                << "\r\n";

    // headers
    for (auto &it : headers)
    {
        response_ss << it.first << ": " << it.second << "\r\n";
    }

    response_ss << "\r\n";

    // message body
    response_ss << message_body;

    return response_ss.str();
}