#include "winsock_utils.h"
#include <signal.h>

SOCKET server_socket = INVALID_SOCKET;

void signal_handler(int signal) {
    printf("\nShutting down server...\n");
    if (server_socket != INVALID_SOCKET) {
        closesocket(server_socket);
    }
    cleanup_winsock();
    exit(0);
}

int main() {
    printf("=== Bare Metal Web Server ===\n");
    printf("Starting server on port %d...\n", PORT);
    
    // Set up signal handler for graceful shutdown
    signal(SIGINT, signal_handler);
    
    // Initialize Winsock
    if (initialize_winsock() != 0) {
        return 1;
    }
    
    // Create server socket
    server_socket = create_server_socket();
    if (server_socket == INVALID_SOCKET) {
        cleanup_winsock();
        return 1;
    }
    
    printf("Server running! Visit: http://localhost:%d\n", PORT);
    printf("Press Ctrl+C to stop the server\n\n");
    
    // Main server loop
    while (1) {
        SOCKET client_socket;
        struct sockaddr_in client_addr;
        int client_addr_size = sizeof(client_addr);
        
        // Accept incoming connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
        
        if (client_socket == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            continue;
        }
        
        // FIXED: Use inet_ntoa instead of inet_ntop for Windows compatibility
        printf("Connection from: %s\n", inet_ntoa(client_addr.sin_addr));
        
        // Handle the client connection
        handle_client_connection(client_socket);
    }
    
    // Cleanup
    closesocket(server_socket);
    cleanup_winsock();
    return 0;
}
