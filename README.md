# Multithreaded HTTP Web Server (C++)

A lightweight multithreaded HTTP web server built from scratch using C++ and Winsock.

## Features

- HTTP request parsing
- Multi-page routing
- Static HTML serving
- CSS file serving
- 404 Not Found handling
- Multithreaded client handling using std::thread
- Winsock socket programming

## Routes

| Route | Description |
|---------|-------------|
| / | Home page |
| /about | About page |
| /contact | Contact page |
| Any other route | 404 Not Found |

## Technologies

- C++
- Winsock2
- Multithreading (std::thread)
- HTTP

## Build

```bash
g++ -std=c++17 src/main.cpp src/Server.cpp src/HttpParser.cpp src/FileManager.cpp -o server.exe -lws2_32
