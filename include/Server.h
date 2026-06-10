#pragma once

#include <winsock2.h>

class Server
{
public:
    void start();

private:
    SOCKET serverSocket;
};