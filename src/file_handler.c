#include "file_handler.h"
#include "http_parser.h"

void serve_file(SOCKET client_socket, const char* uri, int head_only) {
    char filepath[MAX_PATH_SIZE];
    
    // Build file path (remove leading slash and prepend "public/")
    const char* filename = uri + 1; // Skip leading slash
    snprintf(filepath, sizeof(filepath), "public\\%s", filename);
    
    // Replace forward slashes with backslashes for Windows
    for (int i = 0; filepath[i]; i++) {
        if (filepath[i] == '/') {
            filepath[i] = '\\';
        }
    }
    
    // Check if file exists
    HANDLE file = CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (file == INVALID_HANDLE_VALUE) {
        send_error_response(client_socket, 404, "Not Found");
        return;
    }
    
    CloseHandle(file);
    
    // Get content type
    const char* content_type = get_content_type(filename);
    
    // Send file response
    send_file_response(client_socket, filepath, content_type, head_only);
}

const char* get_content_type(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (!ext) return "application/octet-stream";
    
    if (strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0) {
        return "text/html";
    } else if (strcmp(ext, ".css") == 0) {
        return "text/css";
    } else if (strcmp(ext, ".js") == 0) {
        return "application/javascript";
    } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
        return "image/jpeg";
    } else if (strcmp(ext, ".png") == 0) {
        return "image/png";
    } else if (strcmp(ext, ".gif") == 0) {
        return "image/gif";
    } else if (strcmp(ext, ".txt") == 0) {
        return "text/plain";
    }
    
    return "application/octet-stream";
}

void send_file_response(SOCKET client_socket, const char* filepath, const char* content_type, int head_only) {
    HANDLE file = CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (file == INVALID_HANDLE_VALUE) {
        send_error_response(client_socket, 500, "Internal Server Error");
        return;
    }
    
    // Get file size
    DWORD file_size = GetFileSize(file, NULL);
    
    // Send HTTP headers
    char headers[512];
    snprintf(headers, sizeof(headers),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %lu\r\n"
        "Connection: close\r\n"
        "\r\n",
        content_type, file_size);
    
    send(client_socket, headers, strlen(headers), 0);
    
    // Send file content (if not HEAD request)
    if (!head_only) {
        char buffer[4096];
        DWORD bytes_read;
        
        while (ReadFile(file, buffer, sizeof(buffer), &bytes_read, NULL) && bytes_read > 0) {
            send(client_socket, buffer, bytes_read, 0);
        }
    }
    
    CloseHandle(file);
}
