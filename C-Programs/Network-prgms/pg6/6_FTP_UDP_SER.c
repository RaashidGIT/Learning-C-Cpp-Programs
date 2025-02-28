/*
 * UDP File Transfer Server
 * ------------------------
 * This program implements a UDP-based file transfer server.
 * The server listens for a client to send a filename, receives the file data,
 * and writes it to disk.
 *
 * Expected Output:
 * - Displays a message when binding is successful.
 * - Shows the received filename.
 * - Prints the number of bytes received for each chunk.
 * - Indicates when the entire file has been successfully received.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024  // Define buffer size for data transfer

int main() {
    int sockdes, n;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];
    socklen_t c = sizeof(client);
    FILE *file;

    // Create UDP socket
    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        perror("Socket creation failed");  // Handle socket creation failure
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any network interface
    server.sin_port = htons(8888);  // Set the server port to 8888

    // Bind socket
    if (bind(sockdes, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");  // Handle bind failure
        close(sockdes);
        return 1;
    }

    printf("Bind done. Waiting for data...\n");

    // Receive file name from client
    n = recvfrom(sockdes, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &c);
    if (n < 0) {
        perror("Receive failed");  // Handle receive failure
        close(sockdes);
        return 1;
    }
    buffer[n] = '\0';  // Null-terminate received file name

    printf("Receiving file: %s\n", buffer);

    // Open file for writing in binary mode
    file = fopen(buffer, "wb");
    if (!file) {
        perror("File open failed");  // Handle file open failure
        close(sockdes);
        return 1;
    }

    // Receive file data
    while (1) {
        n = recvfrom(sockdes, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &c);
        if (n < 0) {
            perror("Receive failed");  // Handle receive failure
            break;
        }

        // Check for end-of-file marker
        if (n == 1 && buffer[0] == '\0') {
            printf("End of file received.\n");
            break;
        }

        // Write received data to file
        fwrite(buffer, 1, n, file);
        printf("Received %d bytes\n", n);
    }

    printf("File received successfully.\n");

    // Close file and socket
    fclose(file);
    close(sockdes);

    return 0;
}

