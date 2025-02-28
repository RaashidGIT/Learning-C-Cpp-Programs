/*
 * Program: UDP Echo Server
 * 
 * Description:
 * This program implements a simple UDP server that listens on port 8080.
 * It receives messages from clients and echoes them back.
 * 
 * How it Works:
 * - Creates a UDP socket using `socket()`.
 * - Binds the socket to `INADDR_ANY` and port `8080` using `bind()`.
 * - Listens indefinitely for incoming messages from clients.
 * - When a message is received, it is printed to the console.
 * - The server then sends the same message back to the client (echo response).
 * 
 * Expected Output (Example Interaction with a Client):
 * 
 * Server is listening on port 8080...
 * Received from client: Hello, Server!
 * Echoed back to client: Hello, Server!
 *
 * Note:
 * - The server runs in an infinite loop to handle multiple client messages.
 * - To stop the server, use `Ctrl+C`.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Receive data from client
        int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';  // Null-terminate the received data

        printf("Received from client: %s\n", buffer);

        // Echo the data back to the client
        sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&client_addr, addr_len);
        printf("Echoed back to client: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

