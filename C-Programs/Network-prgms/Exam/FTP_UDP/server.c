#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int sockdes, n;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];
    socklen_t c = sizeof(client);
    FILE *file;

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
        close(sockdes);
        return 1;
    }

    printf("Bind done. Waiting for data...\n");

    n = recvfrom(sockdes, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &c);
    if (n < 0) {
        perror("Receive failed");
        close(sockdes);
        return 1;
    }
    buffer[n] = '\0';

    printf("Receiving file: %s\n", buffer);

    file = fopen(buffer, "wb");
    if (!file) {
        perror("File open failed");
        close(sockdes);
        return 1;
    }

    while (1) {
        n = recvfrom(sockdes, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &c);
        if (n < 0) {
            perror("Receive failed");
            break;
        }

        if (n == 1 && buffer[0] == '\0') {
            printf("End of file received.\n");
            break;
        }

        fwrite(buffer, 1, n, file);
        printf("Received %d bytes\n", n);
    }

    printf("File received successfully.\n");

    fclose(file);
    close(sockdes);

    return 0;
}
