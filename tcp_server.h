#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

int tcp_server_init(int port);
int tcp_server_accept(int server_fd);
int tcp_server_send(int client_fd, const char *buf, int len);
void tcp_server_close(int fd);

#endif