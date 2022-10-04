#include "anya.h"
#include "socket.h"

#include <iostream>
#include <unistd.h>

#include <sys/socket.h>

void Anya::get(int path)
{
}

int Anya::accept_connection(int sockfd) {
    int client_fd;
    if ((client_fd = accept(sockfd, (struct sockaddr *)nullptr, nullptr)) == -1)
    {
        perror("accept");
        exit(1);
    }
    std::cout << "Connection received on socket " << client_fd << std::endl;

    return client_fd;
}

void Anya::handle_connection(int sockfd) {
    char buf[1024];
    while (true)
    {
        int nbytes;
        memset(buf, 0, sizeof(buf));
        if ((nbytes = recv(sockfd, buf, sizeof(buf), 0)) <= 0)
        {
            if (nbytes == 0)
            {
                std::cout << "Client disconnected" << std::endl;
                break;
            }
            else
            {
                perror("recv");
            }
        }

        std::cout << "Request: " << buf << std::endl;
    }
}

void Anya::listen(int port)
{
    int sockfd = Socket::listen(port);

    std::cout << "Listening on port " << port << " with sockfd = " << sockfd << std::endl;

    while (true)
    {
        int client_fd = accept_connection(sockfd);
        handle_connection(client_fd);
    }

    close(sockfd);
}