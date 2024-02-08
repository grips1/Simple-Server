#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    //create socket + address options

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(!sockfd)
    {
        perror("Socket File Descriptor");
        return -1;
    }
    int PORT;
    printf("Enter port number for local server\n>");
    scanf("%d", &PORT);
    struct sockaddr peer = {0};
    peer.sa_family = AF_INET;
    socklen_t peer_info_size = sizeof(peer);
    int peer_sockfd;
    struct sockaddr_in socket_info = {0};
    socket_info.sin_family = AF_INET;
    socket_info.sin_port = htons(PORT);
    socklen_t socket_info_size = sizeof(socket_info);

    //bind
    if((bind(sockfd, (struct sockaddr*)& socket_info, socket_info_size)) < 0)
    {
        perror("Bind To Socket Failure!");
        return -1;
    }

    //listen
    if( (listen(sockfd, 1)) < 0)
    {
        perror("Listen Failure!");
        return -1;
    }

    //accept
    peer_sockfd = accept(sockfd, &peer, &peer_info_size);
    if(peer_sockfd < 0)
    {
        perror("Accept Peer Failure");
        return -1;
    }
    char* greeting = "Hello &Welcome.\nMessage limit = 99 chars.\n>";
    size_t greeting_length = strlen(greeting);
    if(write(peer_sockfd, greeting, greeting_length) < 0)
    {
        perror("Write Message Failure!");
        return -1;
    }
    char msg[100];
    read(peer_sockfd, &msg[0], 99); 
    greeting = "Received following message:\n";
    greeting_length = strlen(greeting);
    write(peer_sockfd, greeting, greeting_length);
    write(peer_sockfd, &msg[0], sizeof(msg));
    greeting = "\nMessage received.\n";
    greeting_length = strlen(greeting);
    write(peer_sockfd, greeting, greeting_length);
}
