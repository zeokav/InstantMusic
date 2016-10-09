#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

void handle_client(int newsockfd) {
  int fd = open("./MusicProvider/closer.mp3", O_RDONLY);
  char buff[BUFFER_SIZE + 1];

  if(fd == -1) {
    printf("Could not open file.");
  }
  else {
    //filesize can be used to update progressbar.
    off_t filesize = lseek(fd, 0, SEEK_END);
    printf("\nFile size: %ld, transferring...\n", filesize);

    //reset file pointer
    lseek(fd, 0, SEEK_SET);

    int nob;
    while((nob = read(fd, buff, BUFFER_SIZE)) > 0) {
      send(newsockfd, buff, nob, 0);
    };
    printf("Done.\n");
    close(fd);
  }
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server, client;
    sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = INADDR_ANY;

    printf("Binding server...");

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 5);
    socklen_t clen = sizeof(client);
    int newsockfd;

    while(1) {
        printf("Waiting for client.");
        newsockfd = accept(sockfd, (struct sockaddr *)&client, &clen);
        pid_t pid = fork();
        if(pid == 0) {
            handle_client(newsockfd);
            close(newsockfd);
            exit(1);
        }
    }
    close(sockfd);
    return 0;
}
