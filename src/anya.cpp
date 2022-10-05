#include "anya.h"
#include "socket.h"
#include "request.h"
#include "response.h"
#include "util.h"

#include <iostream>
#include <unistd.h>

#include <sys/socket.h>

void Anya::get(int path)
{
}

int Anya::accept_connection(int masterfd)
{
    int client_fd;
    if ((client_fd = accept(masterfd, (struct sockaddr *)nullptr, nullptr)) == -1)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    return client_fd;
}

void Anya::handle_connection()
{
    char buf[1024];
    while (true)
    {
        int nbytes;
        memset(buf, 0, sizeof(buf));
        if ((nbytes = recv(this->sockfd, buf, sizeof(buf), 0)) <= 0)
        {
            if (nbytes == 0)
            {
                close(this->sockfd);
                break;
            }
            else
            {
                perror("recv");
            }
        }
        handle_request(buf);
    }
}

void Anya::handle_request(const char *raw_request)
{
    std::string request_str = raw_request;
    Request request(request_str);

    Response response = build_response(request);
    std::string response_str = response.response_str();

    send_response(response_str);
}

Response Anya::build_response(const Request &request)
{
    std::stringstream sstream = read_file("." + request.uri);

    Response response("HTTP/1.1", 200, "OK", sstream.str());
    return response;
}

void Anya::send_response(const std::string &response_str)
{
    const char *response_c_str = response_str.c_str();
    if (send(this->sockfd, response_c_str, strlen(response_c_str), 0) == -1)
    {
        perror("send");
    }
}

void Anya::listen(int port)
{
    int sockfd = Socket::listen(port);

    std::cout << "Listening on port " << port << " with sockfd = " << sockfd << std::endl;

    while (true)
    {
        int client_fd = accept_connection(sockfd);
        this->sockfd = client_fd;
        handle_connection();
    }

    close(sockfd);
}