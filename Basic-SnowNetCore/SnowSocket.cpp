#include"SnowSocket.h"
#include"LogCollector.h"

void CSnowSocket::InitSocket(const SOCKET_TYPE socketType, const DWORD dwFlags) {

    switch (socketType) {
    case SOCKET_TYPE::TCP_TYPE:
        socket_ = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, dwFlags);
        break;
    case SOCKET_TYPE::UDP_TYPE:
        socket_ = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, dwFlags);
        break;
    default:
        break;
    }
    if (socket_ == INVALID_SOCKET) {
        std::cout << "Can Not Init Socket" << WSAGetLastError() << "\n";
    }
}

bool CSnowSocket::Bind(const SOCKADDR_IN* sockAddrIn) {

    if (sockAddrIn == nullptr) {
        PRINT_ERROR_LOG("SOCKADDR_IN IS NULLPTR", "ERROR: ", WSAGetLastError());
        return false;
    }

    if (bind(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(sockAddrIn)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        PRINT_ERROR_LOG("BIND", "ERROR: ", WSAGetLastError());
        Close();
        return false;
    }
    return true;
}

bool CSnowSocket::Listen() {

    if (socket_ == INVALID_SOCKET) {
        PRINT_ERROR_LOG("Listen SOCKET IS INVALID_SOCKET", "ERROR: ", WSAGetLastError());
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

bool CSnowSocket::Connect(const SOCKADDR_IN* serverAddr) {

    if (serverAddr == nullptr) {
        PRINT_ERROR_LOG("Coonect SOCKADDR_IN IS nullptr", WSAGetLastError());
        return false;
    }

    if (socket_ == INVALID_SOCKET) {
        PRINT_ERROR_LOG("Connect SOCKET IS INVALID_SOCKET", WSAGetLastError());
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
