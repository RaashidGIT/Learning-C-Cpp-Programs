/*
 * TCP File Transfer Server
 * ------------------------
 * This program implements a TCP-based file transfer server.
 * The server listens on port 8888, accepts a client connection,
 * receives the file name and file data from the client, and writes
 * the data to a file.
 *
 * Expected Output:
 * - Displays a message when the server is listening.
 * - Shows the received file name.
 * - Prints a message when the file is received successfully.
 * - Any errors during the process (e.g., failed to create socket, bind, receive data) will also be displayed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024  // Define buffer size for data transfer

int main() {
    int server_sock, client_sock, n;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Create TCP socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");  // Handle socket creation failure
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any network interface
    server_addr.sin_port = htons(8888);  // Set the server port to 8888

    // Bind socket
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");  // Handle bind failure
        close(server_sock);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_sock, 1) < 0) {
        perror("Listen failed");  // Handle listen failure
        close(server_sock);
        return 1;
    }

    printf("Server listening on port 8888...\n");

    // Accept a client connection
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock < 0) {
        perror("Accept failed");  // Handle accept failure
        close(server_sock);
        return 1;
    }

    printf("Client connected.\n");

    // Receive file name from client
    n = recv(client_sock, buffer, BUFFER_SIZE, 0);
    if (n < 0) {
        perror("Receive failed");  // Handle receive failure
        close(client_sock);
        close(server_sock);
        return 1;
    }
    buffer[n] = '\0';  // Null-terminate the file name

    printf("Receiving file: %s\n", buffer);

    // Open file for writing
    file = fopen(buffer, "wb");
    if (!file) {
        perror("File open failed");  // Handle file open failure
        close(client_sock);
        close(server_sock);
        return 1;
    }

    // Receive file data
    while ((n = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, n, file);  // Write received data to file
    }

    if (n < 0) {
        perror("Receive failed");  // Handle any errors while receiving data
    }

    printf("File received successfully.\n");

    // Close file and sockets
    fclose(file);
    close(client_sock);
    close(server_sock);

    return 0;
}

