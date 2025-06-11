#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>

int main(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        AF_INET,
        htons(9999),
        0
    };

    bind(sockfd, &addr, sizeof(addr));

    listen(sockfd, 10);

    int clientfd = accept(sockfd, 0 ,0);

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

        poll(fds, 2, 5000);

        if (fds[0].revents & POLLIN)
        {
            read(0, buffer, 255);
            send(clientfd, buffer, 255, 0);
        }
        else if (fds[1].revents & POLLIN){
            if (recv(clientfd, buffer, 255, 0) == 0)
            {
                return 0;
            }
            printf("%s\n", buffer);
        }
    }

    return 0;
}