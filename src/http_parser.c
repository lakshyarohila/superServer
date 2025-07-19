#include "http_parser.h"
#include "file_handler.h"

int parse_http_request(const char* raw_request, http_request_t* request) {
    // Find the end of the first line
    const char* line_end = strstr(raw_request, "\r\n");
    if (!line_end) {
        line_end = strstr(raw_request, "\n");
        if (!line_end) return -1;
    }
    
  
    int line_length = line_end - raw_request;
    char request_line[512];
    strncpy(request_line, raw_request, line_length);
    request_line[line_length] = '\0';
    

    char* token = strtok(request_line, " ");
    if (!token) return -1;
    strcpy(request->method, token);
    
    token = strtok(NULL, " ");
    if (!token) return -1;
    strcpy(request->uri, token);
    
    token = strtok(NULL, " ");
    if (!token) return -1;
    strcpy(request->version, token);
    

    const char* headers_start = line_end + (strstr(raw_request, "\r\n") ? 2 : 1);
    strncpy(request->headers, headers_start, MAX_HEADER_SIZE - 1);
    request->headers[MAX_HEADER_SIZE - 1] = '\0';
    
    return 0;
}

void handle_http_request(SOCKET client_socket, http_request_t* request) {
    printf("Request: %s %s %s\n", request->method, request->uri, request->version);
    
    // Only handle GET and HEAD requests
    if (strcmp(request->method, "GET") != 0 && strcmp(request->method, "HEAD") != 0) {
        send_error_response(client_socket, 501, "Not Implemented");
        return;
    }
    
    // Handle root path -- diff routes 
    if (strcmp(request->uri, "/") == 0) {
        strcpy(request->uri, "/index.html");
    }
    
    // Serve the requested file 🟢
    serve_file(client_socket, request->uri, strcmp(request->method, "HEAD") == 0);
}

void send_error_response(SOCKET client_socket, int status_code, const char* status_text) {
    char response[1024];
    char body[512];
    
    // Create error page with status code and message
    snprintf(body, sizeof(body),
        "<!DOCTYPE html>\n"
        "<html><head><title>%d %s</title></head>\n"
        "<body><h1>%d %s</h1></body></html>\n",
        status_code, status_text, status_code, status_text);
    
    // Create http req
    snprintf(response, sizeof(response),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status_code, status_text, (int)strlen(body), body);
    
    send(client_socket, response, strlen(response), 0);
}
