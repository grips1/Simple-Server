#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    //create socket + address options V
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(!sockfd)
    {
        perror("Socket File Descriptor");
        return -1;
    }
    int PORT = 1234;
    struct sockaddr peer = {0};
    peer.sa_family = AF_INET;
    socklen_t peer_info_size = sizeof(peer);
    int peer_sockfd;
    struct sockaddr_in socket_info = {0};
    socket_info.sin_family = AF_INET;
    socket_info.sin_port = htons(PORT);
    socklen_t socket_info_size = sizeof(socket_info);
    //bind V
    if((bind(sockfd, (struct sockaddr*)& socket_info, socket_info_size)) < 0)
    {
        perror("Bind Socket To Address");
        return -1;
    }
    //listen V
    if( (listen(sockfd, 1)) < 0)
    {
        perror("Listening");
        return -1;
    }
    //accept
    peer_sockfd = accept(sockfd, &peer, &peer_info_size);
    if(peer_sockfd < 0)
    {
        perror("Accept Peer Failure");
        return -1;
    }
    //Client
    char* greeting = "Hello, welcome to the dungeon.";
    if(write(peer_sockfd, greeting, 100) < 0)
    {
        perror("Write Message Failure!");
        return -1;
    }
}