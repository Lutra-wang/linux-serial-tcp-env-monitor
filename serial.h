#ifndef _SERIAL_H_
#define _SERIAL_H_

int serial_open(const char *dev);
int serial_config(int fd);
int serial_read_data(int fd, char *buf, int len);
int serial_write_data(int fd, const char *buf, int len);
void serial_close(int fd);

#endif