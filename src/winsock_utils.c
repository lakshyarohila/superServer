#include "winsock_utils.h"
#include "http_parser.h"
#include "file_handler.h"

int initialize_winsock() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return -1;
    }
    
    printf("Winsock initialized successfully\n");
    return 0;
}

SOCKET create_server_socket() {
    SOCKET server_socket;
    struct sockaddr_in server_addr;
    
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }
    
    // Allow socket reuse
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
        printf("Setsockopt failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        return INVALID_SOCKET;
    }
    
    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Bind socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        return INVALID_SOCKET;
    }
    
    // Listen for connections
    if (listen(server_socket, MAX_CLIENTS) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        return INVALID_SOCKET;
    }
    
    printf("Server listening on port %d\n", PORT);
    return server_socket;
}

void cleanup_winsock() {
    WSACleanup();
    printf("Winsock cleaned up\n");
}

void handle_client_connection(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    
    // Receive HTTP request
    bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        
        // Parse and handle HTTP request
        http_request_t request;
        if (parse_http_request(buffer, &request) == 0) {
            handle_http_request(client_socket, &request);
        } else {
            send_error_response(client_socket, 400, "Bad Request");
        }
    }
    
    closesocket(client_socket);
}
