#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int sock, n;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    FILE *file;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Cannot create socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    printf("Connected to server.\n");
    printf("Enter the file name to send: ");
    scanf("%s", buffer);

    if (send(sock, buffer, strlen(buffer), 0) < 0) {
        perror("Send failed");
        close(sock);
        return 1;
    }

    file = fopen(buffer, "rb");
    if (!file) {
        perror("File open failed");
        close(sock);
        return 1;
    }

    while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(sock, buffer, n, 0) < 0) {
            perror("Send failed");
            fclose(file);
            close(sock);
            return 1;
        }
    }

    printf("File sent successfully.\n");

    fclose(file);
    close(sock);

    return 0;
}
