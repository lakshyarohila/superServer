#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_METHOD_SIZE 16
#define MAX_URI_SIZE 256
#define MAX_VERSION_SIZE 16
#define MAX_HEADER_SIZE 1024

typedef struct {
    char method[MAX_METHOD_SIZE];
    char uri[MAX_URI_SIZE];
    char version[MAX_VERSION_SIZE];
    char headers[MAX_HEADER_SIZE];
} http_request_t;

// Function declarations
int parse_http_request(const char* raw_request, http_request_t* request);
void handle_http_request(SOCKET client_socket, http_request_t* request);
void send_error_response(SOCKET client_socket, int status_code, const char* status_text);

#endif
