// This is the server-side code for a simple TCP socket communication program.
// The server listens for client connections, receives messages, and sends responses.

/*
 * Purpose: (Server-side) 
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
    int Sockdes, newsock, c;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];

    // Create socket
    Sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (Sockdes == -1) {
        printf("Cannot Create Socket\n");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind the socket
    if (bind(Sockdes, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Bind Failed\n");
        return 1;
    }
    printf("\nBind done\n");

    // Listen for connections
    listen(Sockdes, 3);
    printf("\nWaiting for Incoming connection....\n");

    c = sizeof(struct sockaddr_in);

    // Accept an incoming connection
    newsock = accept(Sockdes, (struct sockaddr*)&client, (socklen_t*)&c);
    if (newsock < 0) {
        perror("\nAccept Failed\n");
        return 1;
    }
    printf("\nConnection accepted\n");

    // Communication loop
    while (1) {
        recv(newsock, reply, 2000, 0);
        printf("\nFrom client:\n");
        puts(reply);

        printf("\nTo client:\n");
        scanf("%s", msg);
        send(newsock, msg, strlen(msg), 0);
    }

    return 0;
}

