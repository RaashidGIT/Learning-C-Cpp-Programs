/*
 * UDP File Transfer Client
 * ------------------------
 * This program allows a client to send a file to a server using UDP.
 * The client takes a filename as input, sends the filename to the server,
 * and then transmits the file data in chunks.
 * 
 * Expected Output:
 * - Prompts user to enter the file name.
 * - Displays the number of bytes sent for each chunk.
 * - Shows a success message once the file transfer is complete.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024  // Define the buffer size for file transfer

int main() {
    int sockdes, n;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];
    socklen_t server_len = sizeof(server);
    FILE *file;

    // Create UDP socket
    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        perror("Cannot create socket");  // Handle socket creation failure
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // Set the server port to 8888
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {  // Convert IP address
        perror("Invalid address/ Address not supported");
        close(sockdes);
        return 1;
    }

    // Get file name from user
    printf("Enter the file name to send: ");
    scanf("%s", buffer);  // Read file name from user input

    // Send file name to server
    if (sendto(sockdes, buffer, strlen(buffer), 0, (struct sockaddr *)&server, server_len) < 0) {
        perror("Send failed");  // Handle send failure
        close(sockdes);
        return 1;
    }

    // Open the specified file for reading in binary mode
    file = fopen(buffer, "rb");
    if (!file) {
        perror("File open failed");  // Handle file open failure
        close(sockdes);
        return 1;
    }

    // Read and send file data in chunks
    while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (sendto(sockdes, buffer, n, 0, (struct sockaddr *)&server, server_len) < 0) {
            perror("Send failed");  // Handle send failure
            fclose(file);
            close(sockdes);
            return 1;
        }
        printf("Sent %d bytes\n", n);  // Display number of bytes sent
    }

    // Send end-of-file marker to signal completion
    buffer[0] = '\0';  // EOF marker
    if (sendto(sockdes, buffer, 1, 0, (struct sockaddr *)&server, server_len) < 0) {
        perror("Send failed");  // Handle send failure
        fclose(file);
        close(sockdes);
        return 1;
    }

    printf("File sent successfully.\n");  // Confirm successful file transfer

    // Close file and socket
    fclose(file);
    close(sockdes);

    return 0;
}

