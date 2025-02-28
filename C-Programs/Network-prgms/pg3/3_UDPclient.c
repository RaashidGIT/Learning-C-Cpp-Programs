/*
 * Program: Simple UDP Client
 * 
 * Description:
 * This C program implements a simple UDP client that sends a message to 
 * a server running on `127.0.0.1` (localhost) at port `8888` and waits for 
 * a response from the server.
 * 
 * How it Works:
 * - Creates a UDP socket using `socket()`.
 * - Configures the server address (`127.0.0.1:8888`).
 * - Takes user input and sends it to the server using `sendto()`.
 * - Waits for a response from the server using `recvfrom()`.
 * - Displays the received message and closes the socket.
 * 
 * Expected Output (Example Interaction with a Running Server):
 * 
 * Enter a message: Hello
 * From server: Hi there!
 * 
 * Note: This program requires a UDP server running on `127.0.0.1:8888`.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server;
    char msg[2000], reply[2000];
    socklen_t server_len = sizeof(server);

    // Create UDP socket
    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        perror("Cannot create socket");
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // Server port
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {  // Server IP (localhost)
        perror("Invalid address/ Address not supported");
        close(sockdes);
        return 1;
    }

    // Get message from user
    printf("Enter a message: ");
    scanf("%s", msg);

    // Send message to server
    if (sendto(sockdes, msg, strlen(msg), 0, (struct sockaddr *)&server, server_len) < 0) {
        perror("Send failed");
        close(sockdes);
        return 1;
    }

    // Receive reply from server
    if (recvfrom(sockdes, reply, sizeof(reply), 0, (struct sockaddr *)&server, &server_len) < 0) {
        perror("Receive failed");
        close(sockdes);
        return 1;
    }

    // Print the server's reply
    printf("From server: %s\n", reply);

    // Close the socket
    close(sockdes);
    return 0;
}

