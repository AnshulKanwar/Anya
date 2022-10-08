#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <unordered_map>

/*
HTTP-Version Status-Code Reason-Phrase CRLF
headers CRLF
message-body
*/

static std::unordered_map<std::string, std::string> content_type_map = {
    //application
    {".js", "application/javascript"},
    {".json", "application/json"},
    {".pdf", "application/pdf"},
    {".wasm", "application/wasm"},
    {".xml", "application/xml"},

    //font
    {".woff", "image/woff"},
    {".woff2", "image/woff2"},

    //image
    {".gif", "image/gif"},
    {".ico", "image/x-icon"},
    {".jpeg", "image/jpeg"},
    {".jpg", "image/jpeg"},
    {".png", "image/png"},
    {".svg", "image/svg+xml"},
    {".tif", "image/tiff"},
    {".tiff", "image/tiff"},
    {".ttf", "image/ttf"},
    {".webp", "image/webp"},

    //text
    {".css", "text/css"},
    {".htm", "text/html"},
    {".html", "text/html"},
    {".txt", "text/plain"},
};

class Response
{
private:
    std::string http_version;
    std::string reason_phrase;
    std::unordered_map<std::string, std::string> headers;
    std::string message_body;

public:
    int status_code;
    Response(
        std::string http_version,
        int status_code,
        std::string reason_phrase,
        std::string message_body);

    std::string response_str();
    void set_header(const std::string &key, const std::string &value);
    const std::string &get_header(const std::string &key);
};

std::string get_content_type(const std::string &extension);

#endif
