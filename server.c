#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>


#define PORT 9999
#define LOG_ERR perror("Error happened: ")

int main(void)
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        LOG_ERR;
    }

    struct sockaddr_in addr = {
        AF_INET,
        htons(PORT),
        0
    };

    // closing socket more than 1 is not big issue i guess....

    if (bind(sockfd, &addr, sizeof(addr)) == -1)
    {
        LOG_ERR;
        close(sockfd);
    }

    if (listen(sockfd, 10) == -1)
    {
        LOG_ERR;
        close(sockfd);
    }

    int clientfd = accept(sockfd, 0 ,0);
    if (clientfd == -1)
    {
        LOG_ERR;
        close(sockfd);
    }

    struct pollfd fds[2] = {
        {
            0,
            POLLIN,
            0
        },
        {
           clientfd,
            POLLIN,
            0
        }
    };
    while (1)
    {
        char buffer[256] = {0};

        if (poll(fds, 2, 5000) == -1)
        {
            LOG_ERR;
        }

        if (fds[0].revents & POLLIN)
        {
            read(0, buffer, 256);
            send(clientfd, buffer, 256, 0);
        }
        else if (fds[1].revents & POLLIN){
            if (recv(clientfd, buffer, 256, 0) == -1)
            {
                LOG_ERR;
                close(sockfd);
            }
            printf(buffer);
        }
    }
}