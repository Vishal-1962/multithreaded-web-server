#include "../include/Server.h"
#include "../include/HttpParser.h"
#include "../include/FileManager.h"

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

        std::string request(buffer);

        std::string path =
        HttpParser::getPath(request);

        cout << "Requested Path: "
             << path
             << endl;

        std::string html;

std::string filePath;

if (path == "/")
{
    filePath = "pages/index.html";
}
else if (path == "/about")
{
    filePath = "pages/about.html";
}
else if (path == "/contact")
{
    filePath = "pages/contact.html";
}
else
{
    html =
        "<html>"
        "<body>"
        "<h1>404 Not Found</h1>"
        "</body>"
        "</html>";
}

if (!filePath.empty())
{
    html = FileManager::readFile(filePath);
}

if (html.empty())
{
    html =
        "<html>"
        "<body>"
        "<h1>File Not Found</h1>"
        "</body>"
        "</html>";
}

std::string statusLine = "HTTP/1.1 200 OK\r\n";

if (path != "/" &&
    path != "/about" &&
    path != "/contact")
{
    statusLine = "HTTP/1.1 404 Not Found\r\n";
}

std::string response =
    statusLine +
    "Content-Type: text/html\r\n"
    "\r\n" +
    html;

send(
    clientSocket,
    response.c_str(),
    response.length(),
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