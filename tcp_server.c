#include "tcp_server.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int tcp_server_init(int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("socket");
        return -1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        close(server_fd);
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 1) < 0)
    {
        perror("listen");
        close(server_fd);
        return -1;
    }

    return server_fd;
}

int tcp_server_accept(int server_fd)
{
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    if (client_fd < 0)
    {
        perror("accept");
        return -1;
    }

    printf("client connected: %s:%d\n",
           inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    return client_fd;
}

int tcp_server_send(int client_fd, const char *buf, int len)
{
    int n = send(client_fd, buf, len, 0);
    if (n < 0)
    {
        perror("send");
        return -1;
    }

    return n;
}

void tcp_server_close(int fd)
{
    close(fd);
}