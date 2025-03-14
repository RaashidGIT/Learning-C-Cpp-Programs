#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server;
    char msg[2000], reply[2000];
    
    sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdes == -1) {
        printf("\nCannot Create Socket\n");
        return 1;
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (connect(sockdes, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("\nConnection Error\n");
        return 1;
    }
    
    while (1) {
        printf("\nTo Server:\n");
        scanf("%s", msg);
        send(sockdes, msg, strlen(msg), 0);
        
        memset(reply, 0, sizeof(reply));
        recv(sockdes, reply, sizeof(reply), 0);
        printf("\nFrom Server:\n");
        puts(reply);
    }
    
    return 0;
}
