#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 10);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    while (true) {
        int client_socket = accept(server_fd, NULL, NULL);

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n\r\n"
            "Served by backend: " + std::string(hostname) + "\n";

        send(client_socket, response.c_str(), response.length(), 0);
        close(client_socket);
    }

    return 0;
}