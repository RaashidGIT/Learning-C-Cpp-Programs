#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server;
    char msg[2000], reply[2000];
    socklen_t server_len = sizeof(server);

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        perror("Cannot create socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sockdes);
        return 1;
    }

    printf("Enter a message: ");
    scanf("%s", msg);

    if (sendto(sockdes, msg, strlen(msg), 0, (struct sockaddr *)&server, server_len) < 0) {
        perror("Send failed");
        close(sockdes);
        return 1;
    }

    if (recvfrom(sockdes, reply, sizeof(reply), 0, (struct sockaddr *)&server, &server_len) < 0) {
        perror("Receive failed");
        close(sockdes);
        return 1;
    }

    printf("From server: %s\n", reply);

    close(sockdes);
    return 0;
}
