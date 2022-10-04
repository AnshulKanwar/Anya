#ifndef ANYA_H
#define ANYA_H

class Anya
{
private:
public:
    void get(int path);
    int accept_connection(int sockfd);
    void handle_connection(int sockfd);
    void listen(int port);
};

#endif