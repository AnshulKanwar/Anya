#include "anya.h"
#include "socket.h"
#include "request.h"
#include "response.h"
#include "util.h"

#include <spdlog/spdlog.h>

#include <unistd.h>

#include <sys/socket.h>

Anya::Anya(std::string source_dir) : source_dir(source_dir) {}

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
    spdlog::info("Request:\n{}\n\n\n", request_str.substr(0, 600));
    Request request(request_str);

    Response response = build_response(request);
    std::string response_str = response.response_str();

    spdlog::info("Response:\n{}\n\n\n", response_str.substr(0, 600));

    send_response(response_str);
}

Response Anya::build_response(const Request &request)
{
    std::stringstream sstream;

    int status_code;
    std::string reason_phrase;
    std::string filepath;
    std::string filename;

    try
    {
        if (request.uri.compare("/") == 0)
        {
            filename = "/index.html";
        }
        else
        {
            filename = request.uri;
        }

        filepath = this->source_dir + filename;
        sstream = read_file(filepath);

        status_code = 200;
        reason_phrase = "OK";
    }
    catch (std::exception &ex)
    {
        spdlog::error(ex.what());

        filename = "/404.html";
        filepath = this->source_dir + filename;
        sstream = read_file(filepath);

        status_code = 404;
        reason_phrase = "NOT FOUND";
    }

    Response response("HTTP/1.1", status_code, reason_phrase, sstream.str());
    response.set_header("Content-Type", get_content_type(get_extension(filename)));
    return response;
}

void Anya::send_response(const std::string &response_str)
{
    const char *response_c_str = response_str.c_str();
    if (send(this->sockfd, response_c_str, response_str.length(), 0) == -1)
    {
        perror("send");
    }
}

void Anya::listen(int port)
{
    int sockfd = Socket::listen(port);

    spdlog::info("Listening on port {}", port);

    while (true)
    {
        int client_fd = accept_connection(sockfd);
        spdlog::info("Received Connection");
        this->sockfd = client_fd;
        handle_connection();
    }

    close(sockfd);
}