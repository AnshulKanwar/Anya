#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <unordered_map>

/*
Method Request-URI HTTp-Version CRLF
headers CRLF
message-body
*/

enum Method
{
    GET,
    POST,
    PUT,
    DELETE,
};

static std::unordered_map<std::string, Method> const table = {
    {"GET", Method::GET},
    {"POST", Method::POST},
    {"PUT", Method::PUT},
    {"DELETE", Method::DELETE}};

class Request
{
private:
    Method method;
    std::string http_version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    void parse_request(const std::string &raw_request);
    void parse_request_line(const std::string &request_line);

    void parse_method(const std::string &method);
    void parse_uri(const std::string &uri);
    void parse_http_version(const std::string &http_version);

    void parse_header(const std::string &header);
    void parse_body(const std::string &body);

public:
    std::string uri;
    Request(std::string &raw_request);
    std::string get_request_line();
};

#endif