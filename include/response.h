#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <unordered_map>

/*
HTTP-Version Status-Code Reason-Phrase CRLF
headers CRLF
message-body
*/

class Response
{
private:
    std::string http_version;
    int status_code;
    std::string reason_phrase;
    std::unordered_map<std::string, std::string> headers;
    std::string message_body;

public:
    Response(
        std::string http_version,
        int status_code,
        std::string reason_phrase,
        std::string message_body);

    std::string response_str();
};

#endif