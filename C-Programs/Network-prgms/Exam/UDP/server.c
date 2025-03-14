#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes, n;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];
    socklen_t c;

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sockdes, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("Bind done. Waiting for data...\n");

    c = sizeof(client);

    n = recvfrom(sockdes, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&client, &c);
    if (n < 0) {
        perror("Receive failed");
        return 1;
    }
    msg[n] = '\0';

    printf("From client: %s\n", msg);

    printf("Enter reply: ");
    scanf("%s", reply);

    if (sendto(sockdes, reply, strlen(reply), 0, (struct sockaddr *)&client, c) < 0) {
        perror("Send failed");
        return 1;
    }

    printf("Reply sent.\n");

    close(sockdes);
    
    return 0;
}
