#pragma once

#include <winsock2.h>

class Server
{
public:
    void start();
    void handleClient(SOCKET clientSocket);

private:
    SOCKET serverSocket;
};