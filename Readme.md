# 🚀 Bare-Metal HTTP/1.1 Web Server in C


## 🌟 What Makes This Special?

This isn't just another web server - it's a **bare-metal implementation** that gives you complete control over every HTTP byte that flows through your network. Built using only:

- ✅ **Pure C (ISO C99+)** - No frameworks, no shortcuts
- ✅ **Windows Winsock2 API** - Raw socket programming
- ✅ **Windows File API** - Direct file system operations
- ✅ **Zero external dependencies** - Everything from scratch

## 🎯 Features

### ✨ Core Features
- 🌐 **HTTP/1.1 Compliance** - Proper status codes, headers, and protocol handling
- 📁 **Static File Serving** - HTML, CSS, JavaScript, images, and more
- 🎭 **MIME Type Detection** - Automatic Content-Type headers based on file extensions
- 🔍 **Smart Routing** - Handle `/`, custom paths, and default documents
- 🚫 **Error Handling** - Custom 404 pages and proper HTTP error responses
- 💻 **Cross-Platform Ready** - Windows-native with Winsock2

### 🚀 Technical Highlights
- **Socket Programming** - Low-level TCP/IP networking
- **HTTP Parser** - Manual request parsing and response generation
- **File System Integration** - Direct Windows API file operations
- **Memory Safe** - Stack-based buffers with proper bounds checking
- **Resource Management** - Automatic cleanup of sockets and file handles

## 🏗️ Project Structure

```
superweb/
├── 📂 src/
│   ├── 🚀 main.c              # Server entry point and main loop
│   ├── 🔌 winsock_utils.c     # Socket operations and networking
│   ├── 🔌 winsock_utils.h     # Networking interface definitions
│   ├── 📄 http_parser.c       # HTTP/1.1 protocol implementation
│   ├── 📄 http_parser.h       # HTTP parsing interface
│   ├── 📁 file_handler.c      # File serving and MIME detection
│   └── 📁 file_handler.h      # File operations interface
├── 🌐 public/
│   ├── 🏠 index.html          # Homepage
│   ├── ℹ️ about.html           # About page
│   └── 🎨 style.css           # Stylesheet
├── 📊 logs/                   # Server logs (created automatically)
├── 🔧 build.bat               # Build script for Windows
├── 📖 README.md               # This file
└── ⚖️ LICENSE                 # MIT License
```

## 🚀 Quick Start

### 📋 Prerequisites

You'll need one of these compilers on Windows:

**Option 1: Visual Studio (Recommended)**
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/) (Free)
- Make sure to include "Desktop development with C++" workload

**Option 2: MinGW-w64**
- [MinGW-w64](https://www.mingw-w64.org/downloads/) installer
- Add to your Windows PATH environment variable

### 📥 Clone the Repository

```bash
git clone https://github.com/lakshyarohila/SuperServer.git
cd baremetal-server
```

### 🔨 Build the Server

**Using Command Prompt (Recommended):**
```cmd
# Open Command Prompt (Win + R, type 'cmd')
cd path\to\superweb
build.bat
```

**Using PowerShell:**
```powershell
# Open PowerShell
cd path\to\superweb
.\build.bat
```

**Manual Compilation:**
```cmd
mkdir build
gcc -o build/server.exe src/main.c src/winsock_utils.c src/http_parser.c src/file_handler.c -lws2_32
```

### 🎯 Run the Server

```cmd
build\server.exe
```

You should see:
```
=== Bare Metal Web Server ===
Starting server on port 8080...
Winsock initialized successfully
Server listening on port 8080
Server running! Visit: http://localhost:8080
Press Ctrl+C to stop the server
```

### 🌐 Test Your Server

Open your browser and visit:
- 🏠 **Homepage**: [http://localhost:8080](http://localhost:8080)
- ℹ️ **About Page**: [http://localhost:8080/about.html](http://localhost:8080/about.html)
- 🎨 **Stylesheet**: [http://localhost:8080/style.css](http://localhost:8080/style.css)

## 🧪 Sample HTTP Flow

### 📨 Request (Browser → Server)
```http
GET / HTTP/1.1
Host: localhost:8080
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)
Accept: text/html,application/xhtml+xml
```

### 📤 Response (Server → Browser)
```http
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 245
Connection: close



Bare Metal Server
Welcome to Your Bare Metal Web Server!

```

## 🔧 How It Works

### 🔌 Network Layer (`winsock_utils.c`)
- **Socket Creation**: Creates TCP socket using `socket(AF_INET, SOCK_STREAM, 0)`
- **Address Binding**: Binds to `localhost:8080` with `bind()`
- **Connection Listening**: Uses `listen()` to queue incoming connections
- **Client Handling**: Accepts connections with `accept()` and processes them

### 📄 HTTP Layer (`http_parser.c`)
- **Request Parsing**: Manually parses HTTP request line and headers
- **Method Validation**: Supports GET and HEAD methods
- **URI Processing**: Handles routing and default documents
- **Response Generation**: Creates proper HTTP/1.1 responses with headers

### 📁 File Layer (`file_handler.c`)
- **File System Access**: Uses Windows `CreateFile()` and `ReadFile()` APIs
- **MIME Detection**: Maps file extensions to Content-Type headers
- **Streaming**: Efficiently streams files in 4KB chunks
- **Error Handling**: Proper 404 responses for missing files

## 🎓 What You'll Learn

Building this server teaches you:

### 🌐 **Network Programming**
- TCP/IP socket programming on Windows
- Understanding HTTP/1.1 protocol at byte level
- Client-server architecture and connection management

### 💻 **Systems Programming**
- Windows API usage (Winsock2, File APIs)
- Memory management with stack-based buffers
- Resource handling and cleanup patterns

### 🔍 **Web Internals**
- How browsers and servers communicate
- HTTP header structure and purpose
- MIME types and content negotiation
- Status codes and error handling

## 🚀 Future Enhancements

Ready to take it further? Consider adding:

### 🔄 **Concurrency**
- **Multi-threading**: Handle multiple clients simultaneously
- **Thread Pool**: Efficient resource management
- **Async I/O**: Non-blocking operations

### 📊 **Advanced Features**
- **POST Request Handling**: Form data processing
- **Query String Parsing**: Dynamic responses
- **Session Management**: User state tracking
- **Access Logging**: Request monitoring and analytics

### 🔒 **Security & Performance**
- **Rate Limiting**: Prevent abuse
- **Input Validation**: Secure request handling
- **Caching Headers**: Browser cache optimization
- **Compression**: Response size reduction

## 🐛 Troubleshooting

### Common Issues:

**❌ "build.bat is not recognized"**
```cmd
# Use PowerShell-specific syntax:
.\build.bat
# Or switch to Command Prompt
```

**❌ "WSAStartup failed"**
- Ensure you're running on Windows
- Check Windows firewall settings
- Try running as Administrator

**❌ "Bind failed: Address already in use"**
```cmd
# Kill any process using port 8080:
netstat -ano | findstr :8080
taskkill /PID  /F
```

**❌ "GCC not found"**
- Install MinGW-w64 or Visual Studio
- Add compiler to your PATH
- Restart Command Prompt/PowerShell

## 📚 Resources

### 📖 **Learning Materials**
- [HTTP/1.1 Specification (RFC 7230)](https://tools.ietf.org/html/rfc7230)
- [Windows Sockets 2 Reference](https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2)
- [C Programming: A Modern Approach](https://www.knking.com/books/c2/index.html)

### 🛠️ **Development Tools**
- [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)
- [MinGW-w64](https://www.mingw-w64.org/)
- [Wireshark](https://www.wireshark.org/) - Network packet analysis

## 🤝 Contributing

We welcome contributions! Here's how:

1. 🍴 **Fork** the repository
2. 🌿 **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. 💾 **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. 📤 **Push** to the branch (`git push origin feature/amazing-feature`)
5. 🔄 **Open** a Pull Request

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

## 🏆 Acknowledgments

- 🙏 **Inspiration**: The need to understand web servers at the lowest level
- 📚 **Resources**: HTTP/1.1 RFC specifications and Windows socket documentation
- 💡 **Community**: Open source developers building educational projects



### 🎉 You've Built the Foundation of the Web! 🎉

**Star ⭐ this repo if it helped you understand network programming!**





