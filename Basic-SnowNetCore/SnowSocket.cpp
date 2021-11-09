#include"SnowSocket.h"
#include"LogCollector.h"

bool CSnowSocket::OnBind(const SOCKADDR_IN* sockAddrIn)
{

    if (sockAddrIn == nullptr) 
    {
        PRINT_ERROR_LOG("SOCKADDR_IN IS NULLPTR", WSAGetLastError());
        return false;
    }

    if (bind(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(sockAddrIn)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        PRINT_ERROR_LOG("BIND", WSAGetLastError());
        OnClose();
        return false;
    }
    return true;
}

bool CSnowSocket::OnBind(const char* IP, const USHORT port)
{

    SOCKADDR_IN sockAddr;
    ZeroMemory(&sockAddr, sizeof(SOCKADDR_IN));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    inet_pton(AF_INET, IP, &sockAddr.sin_addr);

    if (bind(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(&sockAddr)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) 
    {
        PRINT_ERROR_LOG("BIND", WSAGetLastError());
        OnClose();
        return false;
    }
    return true;
}

bool CSnowSocket::OnListen() 
{

    if (socket_ == INVALID_SOCKET) 
    {
        PRINT_ERROR_LOG("SOCKET IS INVALID_SOCKET", WSAGetLastError());
        return false;
    }

    if (listen(socket_, SOMAXCONN) == SOCKET_ERROR) 
    {
        PRINT_ERROR_LOG("LISTEN IS FAIL", WSAGetLastError());
        OnClose();
        return false;
    }
    return true;
}

bool CSnowSocket::OnClose() 
{

    if (socket_ != INVALID_SOCKET) 
    {
        closesocket(socket_);
        return true;
    }
    return false;
}

bool CSnowSocket::OnShutdown()
{

    if (socket_ != INVALID_SOCKET)
    {
        shutdown(socket_, SD_SEND);
        return true;
    }
    return false;
}

bool CSnowSocket::OnConnect(const SOCKADDR_IN* serverAddr)
{

    if (serverAddr == nullptr)
    {
        PRINT_ERROR_LOG("SOCKADDR_IN IS nullptr", WSAGetLastError());
        return false;
    }

    if (socket_ == INVALID_SOCKET)
    {
        PRINT_ERROR_LOG("SOCKET IS INVALID_SOCKET", WSAGetLastError());
        return false;
    }

    if (connect(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(serverAddr)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) 
    {
        PRINT_ERROR_LOG("COONECT IS FAIL", WSAGetLastError());
        return false;
    }

    return true;
}

SOCKET CSnowSocket::OnAccept(const SOCKADDR* socketAddr)
{
    int32_t addrLen = sizeof(SOCKADDR);
    return  accept(socket_, const_cast<SOCKADDR*>(socketAddr), &addrLen);
}
