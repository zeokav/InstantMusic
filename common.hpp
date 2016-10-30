#ifndef COMMON_HPP
#define COMMON_HPP

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>

#define BUFFER_SIZE 2048
#define NAME_SIZE 100
#define PATH_SIZE 128
#define REQ_FILE 1
#define REQ_LIST 2
#define FUPLOAD 3

struct _control {
  int command;
  int is_error;
};

struct data_block {
  int is_done;
  char data[BUFFER_SIZE + 1];
};

struct header_block {
  int is_req;
  int is_resp;
  int error_code;
  long filesize;
  const char *filename;
};

struct server_info {
  int sockfd;
  sockaddr_in serv;
};

#endif