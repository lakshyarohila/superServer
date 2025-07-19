#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH_SIZE 512
#define MAX_CONTENT_TYPE 64

// Function declarations
void serve_file(SOCKET client_socket, const char* uri, int head_only);
const char* get_content_type(const char* filename);
void send_file_response(SOCKET client_socket, const char* filepath, const char* content_type, int head_only);

#endif
