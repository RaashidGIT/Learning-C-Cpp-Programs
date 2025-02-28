/*
 * Program: TCP Daytime Server
 *
 * Description:
 * This server listens for incoming TCP connections on port 8080.
 * When a client connects, it retrieves the current date and time
 * and sends it to the client before closing the connection.
 *
 * How it Works:
 * - Creates a TCP socket using `socket()`.
 * - Binds the socket to port 8080 and listens for connections.
 * - Accepts incoming client connections.
 * - Retrieves the current system time and formats it.
 * - Sends the formatted date and time string to the client.
 * - Closes the client connection and waits for new connections.
 *
 * Expected Output (Example Interaction with a Client):
 *
 * Server Output:
 * Daytime server is listening on port 8080...
 * Sent date and time to client: 2025-02-28 12:45:30
 *
 * Client Output (using netcat or telnet):
 * $ nc 127.0.0.1 8080
 * 2025-02-28 12:45:30
 *
 * Note:
 * - The server runs indefinitely and serves multiple clients one at a time.
 * - If the port is already in use, change `PORT` to another value.
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>  // Required for socket functions

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in server_addr;
    char buffer[100];
    time_t rawtime;
    struct tm *timeinfo;

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 1) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Daytime server is listening on port %d...\n", PORT);

    while (1) {
        // Accept a new connection
        new_socket = accept(server_fd, NULL, NULL);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Get the current date and time
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

        // Send the date and time to the client
        write(new_socket, buffer, sizeof(buffer));
        printf("Sent date and time to client: %s\n", buffer);

        // Close the connection
        close(new_socket);
    }

    // Close the server socket (this will never be reached in this example)
    close(server_fd);
    return 0;
}

