#include "SnowSession.h"
#include"LogCollector.h"
#include"IocpCore.h"

CSnowSession::CSnowSession(const SOCKET_TYPE socketType, const SessionID sessionID) :
    CSnowSocket(socketType)
	,sessionId_(sessionID)
	,sendComplete_(false)
	,isAlive_(false)
{}

CSnowSession::~CSnowSession()
{
#ifdef PRINT_DEBUG_SESSION_DESTRUCTOR
    PRINT_INFO_LOG("packet size is zero or Overflow", "ID: ", GetSessionID(), "º“∏Í¿⁄ »£√‚");
#endif // PRINT_DEBUG_SESSION_DESTRUCTOR
}

DWORD CSnowSession::OnRecv()
{
    DWORD dwBytes = 0, dwFlags = 0;
    int recvReturn = 0;

    OverlappedEx* pOverEx = new OverlappedRecvEx(this);

    recvReturn = WSARecv(GetSocket(), recvBuffer_.GetWSABuffer(), 1, &dwBytes, &dwFlags, reinterpret_cast<OVERLAPPED*>(pOverEx), NULL);
    if (recvReturn == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSA_IO_PENDING)
        {
            PRINT_ERROR_LOG(" WSARecv ", " ID: ", GetSessionID(), "WSAGetLastError: ", WSAGetLastError(),"\n");
        }
    }
    return dwBytes;
}

DWORD CSnowSession::OnSend()
{
    DWORD dwBytes = 0, dwFlags = 0;
    int sendReturn = 0;

    OverlappedEx* pOverEx = new OverlappedSendEx(this);

    sendReturn = WSASend(GetSocket(), sendBuffer_.GetWSABuffer(), 1, &dwBytes, dwFlags,reinterpret_cast<OVERLAPPED*>(pOverEx), NULL);
    if (sendReturn == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSA_IO_PENDING)
        {
            PRINT_ERROR_LOG(" WSARecv ", " ID: ", GetSessionID(), "WSAGetLastError: ", WSAGetLastError(),"\n");
        }
    }
    return dwBytes;
}

void CSnowSession::PushSendQueue(Packet packet)
{

}

