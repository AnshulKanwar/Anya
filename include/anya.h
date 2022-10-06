#ifndef ANYA_H
#define ANYA_H

#include "request.h"
#include "response.h"

class Anya
{
private:
    int sockfd;
    int accept_connection(int masterfd);
    void handle_connection();
    void handle_request(const char *raw_reqest);
    Response build_response(const Request &request);
    void send_response(const std::string &response_str);

public:
    void listen(int port);
};

#endif