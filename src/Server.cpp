#include "../include/Server.h"

#include <iostream>
#include <winsock2.h>

using namespace std;

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
    cout << "Waiting for client connection..." << endl;

    SOCKET clientSocket =
        accept(serverSocket, nullptr, nullptr);

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Accept failed!" << endl;
    }
    else
    {
        cout << "Client connected!" << endl;

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
}