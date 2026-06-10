#include "../include/Server.h"

#include <iostream>
#include <winsock2.h>
#include <cstring>
#include <thread>

using namespace std;

void Server::handleClient(SOCKET clientSocket)
{
    char buffer[4096];

    int bytesReceived =
        recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0';

        cout << "\n===== HTTP REQUEST =====\n";
        cout << buffer << endl;
        cout << "========================\n";

        const char* response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<html>"
            "<body>"
            "<h1>Hello from Multithreaded C++ Web Server!</h1>"
            "</body>"
            "</html>";

        send(
            clientSocket,
            response,
            strlen(response),
            0
        );
    }

    closesocket(clientSocket);
}

void Server::start()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup failed!" << endl;
        return;
    }

    cout << "Winsock initialized successfully!" << endl;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return;
    }

    cout << "Socket created successfully!" << endl;

    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket,
             (sockaddr*)&serverAddress,
             sizeof(serverAddress)) == SOCKET_ERROR)
    {
        cout << "Bind failed!" << endl;

        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    cout << "Bind successful on port 8080!" << endl;

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Listen failed!" << endl;

        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    cout << "Server listening on port 8080..." << endl;

    while (true)
{
    cout << "\nWaiting for client connection..." << endl;

    SOCKET clientSocket =
        accept(serverSocket, nullptr, nullptr);

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Accept failed!" << endl;
        continue;
    }

    cout << "Client connected!" << endl;

    std::thread clientThread(
        &Server::handleClient,
        this,
        clientSocket
    );

    clientThread.detach();
}

    closesocket(serverSocket);
    WSACleanup();
}