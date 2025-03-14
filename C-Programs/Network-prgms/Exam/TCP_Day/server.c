#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in server_addr;
    char buffer[100];
    time_t rawtime;
    struct tm *timeinfo;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Daytime server is listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, NULL, NULL);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

        write(new_socket, buffer, sizeof(buffer));
        printf("Sent date and time to client: %s\n", buffer);

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
