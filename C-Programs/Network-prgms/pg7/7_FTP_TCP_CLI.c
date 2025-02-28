/*
 * TCP File Transfer Client
 * -------------------------
 * This program implements a TCP-based file transfer client.
 * The client connects to a server on localhost (127.0.0.1) at port 8888,
 * sends the file name, and then transmits the contents of the file to the server.
 *
 * Expected Output:
 * - Displays a message when the connection to the server is successful.
 * - Prompts the user to enter the file name to send.
 * - Shows a message when the file is sent successfully.
 * - Any errors during the process (e.g., failed to create socket, connect, send data) will also be displayed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024  // Define buffer size for data transfer

int main() {
    int sock, n;  // Declare 'n' here to store the number of bytes sent/received
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Cannot create socket");  // Handle socket creation failure
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);  // Set the server port to 8888
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {  // Server IP (localhost)
        perror("Invalid address/ Address not supported");  // Handle invalid address
        close(sock);
        return 1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");  // Handle connection failure
        close(sock);
        return 1;
    }

    printf("Connected to server.\n");

    // Get file name from user
    printf("Enter the file name to send: ");
    scanf("%s", buffer);

    // Send file name to server
    if (send(sock, buffer, strlen(buffer), 0) < 0) {
        perror("Send failed");  // Handle send failure (e.g., network issues)
        close(sock);
        return 1;
    }

    // Open file for reading
    file = fopen(buffer, "rb");
    if (!file) {
        perror("File open failed");  // Handle file open failure
        close(sock);
        return 1;
    }

    // Send file data
    while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(sock, buffer, n, 0) < 0) {
            perror("Send failed");  // Handle send failure during file transmission
            fclose(file);
            close(sock);
            return 1;
        }
    }

    printf("File sent successfully.\n");

    // Close file and socket
    fclose(file);
    close(sock);

    return 0;
}

