#include "socket.h"

#include <spdlog/spdlog.h>

#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int Socket::socket(int port)
{
    struct addrinfo hints, *res;
    int status;
    int sockfd;
    int yes = 1;

    std::string port_str = std::to_string(port);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(nullptr, port_str.c_str(), &hints, &res)) != 0)
    {
        spdlog::error("getaddrinfo error: {}", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    if ((sockfd = ::socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    return sockfd;
}

int Socket::listen(int port)
{
    int sockfd = Socket::socket(port);

    if (::listen(sockfd, 10) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    return sockfd;
}