#include"SnowSocket.h"
#include"LogCollector.h"

bool CSnowSocket::Bind(const SOCKADDR_IN* sockAddrIn) {

    if (sockAddrIn == nullptr) {
        PRINT_ERROR_LOG("SOCKADDR_IN IS NULLPTR", WSAGetLastError());
        return false;
    }

    if (bind(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(sockAddrIn)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        PRINT_ERROR_LOG("BIND", WSAGetLastError());
        Close();
        return false;
    }
    return true;
}

bool CSnowSocket::Bind(const char* IP, const USHORT port, const USHORT sinFamily) {

    if ((sinFamily != AF_INET) || (sinFamily != AF_INET6))PRINT_ERROR_LOG("BIND_sinFamily value is Invalid"); return false;

    SOCKADDR_IN sockAddr;
    ZeroMemory(&sockAddr, sizeof(SOCKADDR_IN));
    sockAddr.sin_family = sinFamily;
    sockAddr.sin_port   = htons(port);
    inet_pton(sinFamily, IP, &sockAddr.sin_addr);

    if (bind(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(&sockAddr)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        PRINT_ERROR_LOG("BIND", WSAGetLastError());
        Close();
        return false;
    }
    return false;
}

bool CSnowSocket::Listen() {

    if (socket_ == INVALID_SOCKET) {
        PRINT_ERROR_LOG("SOCKET IS INVALID_SOCKET", WSAGetLastError());
        return false;
    }

    if (listen(socket_, SOMAXCONN) == SOCKET_ERROR) {
        PRINT_ERROR_LOG("LISTEN IS FAIL", WSAGetLastError());
        Close();
        return false;
    }
    return true;
}

bool CSnowSocket::Close() {

    if (socket_ != INVALID_SOCKET) {
        closesocket(socket_);
        return true;
    }
    return false;
}

bool CSnowSocket::Shutdown(){

    if (socket_ != INVALID_SOCKET) {
        shutdown(socket_,SD_SEND);
        return true;
    }
    return false;
}

bool CSnowSocket::Connect(const SOCKADDR_IN* serverAddr) {

    if (serverAddr == nullptr) {
        PRINT_ERROR_LOG("SOCKADDR_IN IS nullptr", WSAGetLastError());
        return false;
    }

    if (socket_ == INVALID_SOCKET) {
        PRINT_ERROR_LOG("SOCKET IS INVALID_SOCKET", WSAGetLastError());
        return false;
    }

    if (connect(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(serverAddr)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        PRINT_ERROR_LOG("COONECT IS FAIL", WSAGetLastError());
        return false;
    }

    return true;
}

SOCKET CSnowSocket::Accept(const SOCKADDR* socketAddr) {
    int32_t addrLen = sizeof(SOCKADDR);
    return  accept(socket_, const_cast<SOCKADDR*>(socketAddr), &addrLen);
}
