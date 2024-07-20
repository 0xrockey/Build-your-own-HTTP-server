#include <a.out.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // Create a server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // Check if socket creation was successful
    if (server_fd < 0)
    {
        std::cerr << "Failed to create server socket\n";
        return 1;
    }

    // Since the tester restarts your program quite often, setting SO_REUSEADDR
    // ensures that we don't run into 'Address already in use' errors
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        std::cerr << "setsockopt failed\n";
        return 1;
    }
    // Bind to port 4221
    struct sockaddr_in server_addr;
    // AF_INET is the address family for IPv4
    server_addr.sin_family = AF_INET;
    // INADDR_ANY is the address that the server will accept connections from
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // INADDR_ANY is the port that the server will accept connections from
    server_addr.sin_port = htons(4221);
    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
    {
        std::cerr << "Failed to bind to port 4221\n";
        return 1;
    }
    // Listen for incoming connections
    int connection_backlog = 5;
    // Listen for incoming connections
    if (listen(server_fd, connection_backlog) != 0)
    {
        std::cerr << "listen failed\n";
        return 1;
    }
    // Accept an incoming connection
    struct sockaddr_in client_addr;
    // Accept an incoming connection
    int client_addr_len = sizeof(client_addr);
    std::cout << "Waiting for a client to connect...\n";
    // Accept an incoming connection
    accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
    std::cout << "Client connected\n";
    // Close the server socket
    close(server_fd);
    return 0;
}
