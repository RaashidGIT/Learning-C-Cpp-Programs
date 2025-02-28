/*
 * Program: TCP Daytime Client
 *
 * Description:
 * This client connects to a TCP daytime server running on `127.0.0.1:8080`.
 * Once connected, it receives the current date and time from the server
 * and displays it before closing the connection.
 *
 * Expected Output (Example Interaction with the Server):
 *
 * Server Output (from the daytime server):
 * Daytime server is listening on port 8080...
 * Sent date and time to client: 2025-02-28 12:45:30
 *
 * Client Output:
 * Server date and time: 2025-02-28 12:45:30
 *
 * Note:
 * - Ensure the daytime server is running before executing this client.
 * - If the server is on a different machine, update the IP address in `inet_addr()`.
 */

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>  // Required for socket functions

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[100];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Connect to localhost

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    // Receive the date and time from the server
    read(sockfd, buffer, sizeof(buffer));
    printf("Server date and time: %s\n", buffer);

    // Close the socket
    close(sockfd);
    return 0;
}

