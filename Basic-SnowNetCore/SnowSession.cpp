#include "SnowSession.h"
#include"LogCollector.h"

CSnowSession::CSnowSession(const SOCKET_TYPE socketType, const SessionID sessionID) :
	sessionId_(sessionID)
	,sendComplete_(false)
	,isAlive_(false)
{
    InitSocket(socketType);
}

CSnowSession::CSnowSession(const uint32_t BUFFER_SIZE) :
    sessionId_(0)
    , sendComplete_(false)
    , isAlive_(false)
{
}

CSnowSession::~CSnowSession() {
#ifdef PRINT_DEBUG_SESSION_DESTRUCTOR
    PRINT_INFO_LOG("packet size is zero or Overflow", "ID: ", GetSessionID(), "소멸자 호출");
#endif // PRINT_DEBUG_SESSION_DESTRUCTOR
}

bool CSnowSession::PacketValidCheck(const char* packet) {
	//if (packet[0] <= 0 || packet[0] >= sizeof(PACKET_SIZE)) {
	//	PRINT_ERROR_LOG("packet size is zero or Overflow",
	//		"ID: ", GetSessionID(),
	//		"packetSize: ", static_cast<PACKET_SIZE>(packet[0]));
	//	return false;
	//}
	return true;
}

DWORD CSnowSession::OnRecv() {
    DWORD dwBytes = 0, dwFlags = 0;
    int recvReturn = 0;

    // PostRecv()함수 만들기
    recvReturn = WSARecv(GetSocket(), recvBuffer_.GetWSABuffer(), 1, &dwBytes, &dwFlags, NULL, NULL);
    if (recvReturn == SOCKET_ERROR) {
        if (WSAGetLastError() != WSA_IO_PENDING) {
            PRINT_ERROR_LOG(" WSARecv ", " ID: ", GetSessionID(), "WSAGetLastError: ", WSAGetLastError());
        }
    }
    return dwBytes;
}

DWORD CSnowSession::OnSend() {
    DWORD dwBytes = 0, dwFlags = 0;
    int sendReturn = 0;

    sendReturn = WSASend(GetSocket(), sendBuffer_.GetWSABuffer(), 1, &dwBytes, dwFlags, NULL, NULL);
    if (sendReturn == SOCKET_ERROR) {
        if (WSAGetLastError() != WSA_IO_PENDING) {
            PRINT_ERROR_LOG(" WSARecv ", " ID: ", GetSessionID(), "WSAGetLastError: ", WSAGetLastError());
        }
    }
    return dwBytes;
}

void CSnowSession::PushSendQueue(Packet packet) {

    if (PacketValidCheck(reinterpret_cast<char*>(packet)) == false) return;

   /* m_sendQueue.push(packet);

    void* ptr = nullptr;
    if (m_sendQueue.try_pop(ptr) && m_amSendComplte) {
        m_amSendComplte.store(false);
        OnSend(ptr);
    }*/
}

