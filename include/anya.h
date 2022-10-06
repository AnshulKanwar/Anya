#ifndef ANYA_H
#define ANYA_H

#include "request.h"
#include "response.h"

class Anya
{
private:
    //TODO: Assert on sockfd
    int sockfd;
    std::string source_dir;
    int accept_connection(int masterfd);
    void handle_connection();
    void handle_request(const char *raw_reqest);
    Response build_response(const Request &request);
    void send_response(const std::string &response_str);

public:
    Anya(std::string source_dir);
    void listen(int port);
};

#endif