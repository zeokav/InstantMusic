#define BUFFER_SIZE 4096
#define NAME_SIZE 100

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
  char filename[NAME_SIZE];
};
