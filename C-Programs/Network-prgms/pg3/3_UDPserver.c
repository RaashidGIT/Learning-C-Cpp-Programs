/*
 * Program: Simple UDP Server
 * 
 * Description:
 * This C program implements a basic UDP server that listens on port `8888` for 
 * incoming messages from a client, displays the received message, and sends a 
 * response back to the client.
 * 
 * How it Works:
 * - Creates a UDP socket using `socket()`.
 * - Binds the socket to `INADDR_ANY` (any available IP) and port `8888` using `bind()`.
 * - Waits for a message from a client using `recvfrom()`.
 * - Displays the received message.
 * - Takes a response message from the user and sends it back to the client using `sendto()`.
 * 
 * Expected Output (Example Interaction with a Running Client):
 * 
 * Bind done. Waiting for data...
 * From client: Hello
 * Enter reply: Hi there!
 * Reply sent.
 * 
 * Note: This program should be run before the client connects to ensure it is ready to receive messages.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes, n;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];
    socklen_t c;

    // Create socket
    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind socket
    if (bind(sockdes, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("Bind done. Waiting for data...\n");

    c = sizeof(client);

    // Receive message from client
    n = recvfrom(sockdes, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&client, &c);
    if (n < 0) {
        perror("Receive failed");
        return 1;
    }
    msg[n] = '\0';  // Null-terminate received message

    printf("From client: %s\n", msg);

    // Get reply from server user
    printf("Enter reply: ");
    scanf("%s", reply);

    // Send reply to client
    if (sendto(sockdes, reply, strlen(reply), 0, (struct sockaddr *)&client, c) < 0) {
        perror("Send failed");
        return 1;
    }

    printf("Reply sent.\n");

    // Close socket
    close(sockdes);
    
    return 0;
}

