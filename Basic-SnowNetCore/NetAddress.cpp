#include "NetAddress.h"
#include"LogCollector.h"

CNetAddress::CNetAddress()
{
    Init();
}

void CNetAddress::Init()
{
    ZeroMemory(&stSockAddrInfor_, sizeof(stSockAddrInfor_));
}

void CNetAddress::SetAddrInfor(const PSOCKADDR addrinfor)
{
    memcpy_s(&stSockAddrInfor_, sizeof(SOCKADDR_IN), addrinfor, sizeof(SOCKADDR_IN));
}

//Only Ipv4
void CNetAddress::SetAddrInfor(const char* ip, const USHORT port)
{
    if (ip == nullptr)return;

    stSockAddrInfor_.sin_family = AF_INET;
    stSockAddrInfor_.sin_port = htons(port);
    inet_pton(AF_INET, ip, &stSockAddrInfor_.sin_addr);
}

void CNetAddress::PrintIPAndPort()const
{
    char buf[32]{ 0 };      //4Byte
    inet_ntop(AF_INET, &stSockAddrInfor_.sin_addr, buf, sizeof(buf));
    PRINT_INFO_LOG("IP:", buf, "PORT:", ntohs(stSockAddrInfor_.sin_port));
}

const PSOCKADDR_IN CNetAddress::GetAddrInfor()
{
    return &stSockAddrInfor_;
}



