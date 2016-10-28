#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <iostream>

#include "../common.hpp"

void send_file(int sockfd) {
    printf("Client wants a file...\n");

    char s_name[NAME_SIZE];
    int bytes = recv(sockfd, s_name, NAME_SIZE, 0);
    if(bytes > 0) {
        printf("Client wants file: %s", s_name);
        char path[PATH_SIZE] = "./MusicProvider/";
        strcat(path, s_name);  
    }

    
    int fd = open("./MusicProvider/closer.mp3", O_RDONLY);
    char buff[BUFFER_SIZE + 1];

    if(fd == -1) {
        printf("Could not open file.");
        header_block head;
        head.error_code = 1;
    }
    else {

        header_block head;
        head.is_req = 0;
        head.is_resp = 1;

        //filesize can be used to update progressbar.
        off_t filesize = lseek(fd, 0, SEEK_END);
        printf("\nFile size: %ld, transferring...\n", filesize);

        head.filesize = filesize;

        //reset file pointer
        lseek(fd, 0, SEEK_SET);
        head.error_code = 0;
        send(sockfd, (header_block *)&head, sizeof(head), 0);

        int nob;
        while((nob = read(fd, buff, BUFFER_SIZE)) > 0) {
          send(sockfd, buff, nob, 0);
        };
        printf("Done.\n");
        close(fd);
    }
}

void send_listing(int sockfd) {
    printf("Sending listing\n");
    system("ls ./MusicProvider/ > listing.txt");
    int fd = open("./listing.txt", O_RDONLY);
    if(fd == -1) {
        printf("Error fetching the songlist\n");
        return;
    }
    char buff[BUFFER_SIZE + 1];
    int nob;
    while((nob = read(fd, buff, BUFFER_SIZE)) > 0) {
        send(sockfd, buff, nob, 0);
    }
}


void handle_client(int cli_sockfd) {
    std::cout << "A client has been connected." << std::endl;

    while(1) {
        _control ctrl;
        std::cout << "Waiting for command" << std::endl;
        int bytes = recv(cli_sockfd, (_control *)&ctrl, sizeof(ctrl), 0);
        if(bytes > 0) {
            if(ctrl.is_error) {
                printf("Error on client side.\n");
                break;
            }
            else {
                switch(ctrl.command) {
                    case -1: 
                        std::cout << "Closing client connection.";
                        return;
                    case REQ_FILE: send_file(cli_sockfd);
                        break;
                    case REQ_LIST: send_listing(cli_sockfd);
                        break;
                }
            }    
        }
        else {
            std::cerr << "Connection dropped by client" << std::endl;
            exit(-1);
        }

    }
}

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Please specify port.\n");
        return 1;
    }
    int port = atoi(argv[1]);

    int sockfd;
    struct sockaddr_in server, client;
    sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    fflush(stdout);
    std::cout << "Binding server..." << std::endl;

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 5);
    socklen_t clen = sizeof(client);
    int newsockfd;

    std::cout << "Server is up. Port number: "<< port << std::endl;

    while(1) {
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
