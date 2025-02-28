/*
 * Program: Simple TCP Client
 * 
 * Description:
 * This C program implements a simple TCP client that connects to a server
 * running on `127.0.0.1` (localhost) at port `8888`. It allows the user to 
 * send messages to the server and receive responses.
 * 
 * How it Works:
 * - Creates a socket using the `socket()` function.
 * - Connects to a TCP server using `connect()`.
 * - Continuously sends user input to the server and displays received messages.
 * - Uses `send()` to transmit messages and `recv()` to receive responses.
 * 
 * Expected Output (Example Interaction with a Running Server):
 * 
 * To Server:
 * Hello
 * 
 * From Server:
 * Hi, Client!
 * 
 * To Server:
 * How are you?
 * 
 * From Server:
 * I am good. How about you?
 * 
 * Note: The program assumes a server is running on `127.0.0.1:8888`.
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
    
    // Create socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdes == -1) {
        printf("\nCannot Create Socket\n");
        return 1;
    }
    
    // Setup server details
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Connect to localhost
    
    // Connect to server
    if (connect(sockdes, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("\nConnection Error\n");
        return 1;
    }
    
    // Communicate with server
    while (1) {
        printf("\nTo Server:\n");
        scanf("%s", msg);
        send(sockdes, msg, strlen(msg), 0);  // Send message to server
        
        // Receive reply from server
        memset(reply, 0, sizeof(reply));  // Clear buffer
        recv(sockdes, reply, sizeof(reply), 0);
        printf("\nFrom Server:\n");
        puts(reply);
    }
    
    return 0;
}

