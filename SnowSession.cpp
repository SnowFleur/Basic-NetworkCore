#include "SnowSession.h"

CSnowSession::CSnowSession(const SOCKET_TYPE socketType, const SessionID sessionID, const uint32_t BUFFER_SIZE) :
    socket_{ socketType },
	sendComplete_(true),
	sendBuffer_{ BUFFER_SIZE },
	recvBuffer_{ BUFFER_SIZE }
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

bool CSnowSession::OnRecv() {
    DWORD dwBytes	= 0, dwFlags = 0;
    int recvReturn	= 0;

	// PostRecv()함수 만들기
	recvReturn = WSARecv(socket_.GetSocket(), recvBuffer_.GetWSABuffer(), 1, &dwBytes, &dwFlags, NULL, NULL);
	if (recvReturn == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			//PRINT_ERROR_LOG(" WSARecv ", " ID: ", GetSessionID(), "WSAGetLastError: ", WSAGetLastError());
			std::cout << " WSARecv " << " ID: " << GetSessionID() << "WSAGetLastError: " << WSAGetLastError() << "\n";
		}
	}
    return true;
}

bool CSnowSession::OnSend(void* packet) {
	DWORD dwBytes = 0, dwFlags = 0;
	int sendReturn = 0;

	char* p = reinterpret_cast<char*>(packet);

	//패킷 상태 체크
    if (PacketValidCheck(p) == false) return false;

    sendReturn = WSASend(socket_.GetSocket(),sendBuffer_.GetWSABuffer(), 1, &dwBytes, dwFlags, NULL, NULL);
    if (sendReturn == SOCKET_ERROR) {
        if (WSAGetLastError() != WSA_IO_PENDING) {
            //PRINT_ERROR_LOG(" WSARecv ", " ID: ", GetSessionID(), "WSAGetLastError: ", WSAGetLastError());
            std::cout << " WSASend " << " ID: " << GetSessionID() << "WSAGetLastError: " << WSAGetLastError() << "\n";
        }
    }

    return true;
}

void CSnowSession::PostSend(void* packet, DWORD ioByte) {

	//// N-Send를 진행한다.
	//// 패킷이 다 안갈 수 있기 때문에 그거에 대한 처리를 진행한다.


	////남은 데이터가 있는지 체크
	////전부다 보낸게 아니다.
	//// if(보낸 패킷량 <ioByte)
	//if (false) {

	//	// ref카운터 또 증가
	//	// 이 카운터가 어느 이상 넘어가면 그 세션을 자른다.
	//	InCrementSendRef();

	//	//패킷이 남아있으니 다시 Send
	//	OnSend(packet);
	//}

	//else {
	//	// ref카운터 감소
	//	DeCrementSendRef();

	//	// SendQueue Pop
	//	delete packet;

	//	// std::cout << "Before Delete\n";
	//	// delete m_sendQueue.front();
	//	// std::cout << "After Delete\n";

	//	 // Queue가 남아있다면 다음꺼 전송
	//	void* ptr = nullptr;
	//	if (m_sendQueue.try_pop(ptr)) {
	//		OnSend(ptr);
	//	}
	//	//아니라면 sendComplet true
	//	else {
	//		m_amSendComplte.store(true);
	//	}
	//}
}



void CSnowSession::PushSendQueue(void* packet) {
   /* m_sendQueue.push(packet);

    void* ptr = nullptr;
    if (m_sendQueue.try_pop(ptr) && m_amSendComplte) {
        m_amSendComplte.store(false);
        OnSend(ptr);
    }*/
}

