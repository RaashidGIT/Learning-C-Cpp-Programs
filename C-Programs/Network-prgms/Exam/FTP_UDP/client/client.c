#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int sockdes, n;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];
    socklen_t server_len = sizeof(server);
    FILE *file;

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

    printf("Enter the file name to send: ");
    scanf("%s", buffer);

    if (sendto(sockdes, buffer, strlen(buffer), 0, (struct sockaddr *)&server, server_len) < 0) {
        perror("Send failed");
        close(sockdes);
        return 1;
    }

    file = fopen(buffer, "rb");
    if (!file) {
        perror("File open failed");
        close(sockdes);
        return 1;
    }

    while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (sendto(sockdes, buffer, n, 0, (struct sockaddr *)&server, server_len) < 0) {
            perror("Send failed");
            fclose(file);
            close(sockdes);
            return 1;
        }
        printf("Sent %d bytes\n", n);
    }

    buffer[0] = '\0';
    if (sendto(sockdes, buffer, 1, 0, (struct sockaddr *)&server, server_len) < 0) {
        perror("Send failed");
        fclose(file);
        close(sockdes);
        return 1;
    }

    printf("File sent successfully.\n");

    fclose(file);
    close(sockdes);

    return 0;
}
