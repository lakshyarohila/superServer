#ifndef WINSOCK_UTILS_H
#define WINSOCK_UTILS_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 4096
#define MAX_CLIENTS 10

// Function declarations
int initialize_winsock();
SOCKET create_server_socket();
void cleanup_winsock();
void handle_client_connection(SOCKET client_socket);

#endif
