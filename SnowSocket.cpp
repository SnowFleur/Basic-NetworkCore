#include"SnowSocket.h"

bool CSnowSocket::Bind(const SOCKADDR_IN* sockAddrIn) {

    if (sockAddrIn == nullptr) {
        std::cout << "SOCKADDR_IN IS NULLPTR" << WSAGetLastError() << "\n";
        return false;
    }

    if (bind(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(sockAddrIn)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        std::cout << "ERROR_BIND"<<WSAGetLastError() << "\n";
        Close();
        return false;
    }
    return true;
}

bool CSnowSocket::Listen() {

    if (socket_ == INVALID_SOCKET) {
        std::cout << "SOCKET IS INVALID_SOCKET"<<WSAGetLastError() << "\n";
        return false;
    }

    if (listen(socket_, SOMAXCONN) == SOCKET_ERROR) {
        //PRINT_ERROR_LOG("LISTEN IS FAIL", WSAGetLastError());
        std::cout << "LISTEN IS FAIL" << WSAGetLastError() << "\n";
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
        //PRINT_ERROR_LOG("SOCKADDR_IN IS nullptr", WSAGetLastError());
        std::cout << "SOCKADDR_IN IS nullptr" << WSAGetLastError() << "\n";

        return false;
    }

    if (socket_ == INVALID_SOCKET) {
       // PRINT_ERROR_LOG("SOCKET IS INVALID_SOCKET", WSAGetLastError());
        std::cout << "SOCKET IS INVALID_SOCKET" << WSAGetLastError() << "\n";
        return false;
    }

    if (connect(socket_, reinterpret_cast<SOCKADDR*>(const_cast<SOCKADDR_IN*>(serverAddr)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
       // PRINT_ERROR_LOG("COONECT IS FAIL", WSAGetLastError());
        std::cout << "COONECT IS FAIL" << WSAGetLastError() << "\n";
        return false;
    }

    return true;
}

SOCKET CSnowSocket::Accept(const SOCKADDR* socketAddr){
    
    int32_t addrLen = sizeof(SOCKADDR);

    SOCKET tempSocket = INVALID_SOCKET;
    tempSocket = accept(socket_, const_cast<SOCKADDR*>(socketAddr), &addrLen);
    return tempSocket;
}
