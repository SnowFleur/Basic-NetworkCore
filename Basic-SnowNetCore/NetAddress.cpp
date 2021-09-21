#include"NetAddress.h"
#include"LogCollector.h"

CNetAddress::CNetAddress(){
    Init();
}

void CNetAddress::Init(){
    ZeroMemory(&acceptClientInfor_, sizeof(acceptClientInfor_));
}

void CNetAddress::SetAddrInfor(const PSOCKADDR addrinfor) {
    memcpy_s(&acceptClientInfor_, sizeof(SOCKADDR_IN), addrinfor, sizeof(SOCKADDR_IN));
}

void CNetAddress::PrintIPAndPort()const{
    char buf[32]{ 0 };      //4Byte
    inet_ntop(AF_INET, &acceptClientInfor_.sin_addr, buf, sizeof(buf));
    PRINT_INFO_LOG("Accpet IP:", buf,"PORT:",ntohs(acceptClientInfor_.sin_port));
}

const PSOCKADDR_IN CNetAddress::GetAddrInfor() {
    return &acceptClientInfor_;
}



