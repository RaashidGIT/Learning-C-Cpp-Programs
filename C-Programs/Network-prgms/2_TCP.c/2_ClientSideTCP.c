// This is the client-side code for a simple TCP socket communication program.
// The client connects to the server, sends messages, and receives responses.

/*
 * Purpose: (Client-side)
 * This program implements a simple TCP server that:
 * 1. Listens on port 8888.
 * 2. Accepts a client connection.
 * 3. Exchanges messages with the client: receives a message, prints it, and sends a reply back to the client.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int Sockdes;
    struct sockaddr_in client;
    char msg[2000], reply[2000];

    // Create socket
    Sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (Sockdes == -1) {
        printf("\nCannot Create Socket\n");
        return 1;
    }

    // Prepare the sockaddr_in structure
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(8888);

    // Connect to server
    if (connect(Sockdes, (struct sockaddr*)&client, sizeof(client)) < 0) {
        printf("\nConnection Error\n");
        return 1;
    }

    // Communication loop
    while (1) {
        printf("\nTo Server:\n");
        scanf("%s", msg);
        send(Sockdes, msg, strlen(msg), 0);

        recv(Sockdes, reply, 2000, 0);
        printf("\nFrom Server:\n");
        puts(reply);
    }

    return 0;
}

