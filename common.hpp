#define BUFFER_SIZE 2048

struct _control {
  int command;
  int is_error;
  int is_data;
};

struct _block {
  int is_error;
  int is_data;
  int error_code;
  char data[BUFFER_SIZE];
};
