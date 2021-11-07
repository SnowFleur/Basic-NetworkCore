#include "SnowServer.h"

CSnowServer::CSnowServer(const uint32_t workerThreadCount) :
    WORKER_THREAD_COUNT(workerThreadCount)
{
    vecWorkerThread_.reserve(WORKER_THREAD_COUNT);
}

CSnowServer::~CSnowServer() noexcept
{

}


void CSnowServer::StartServer(const char* pServerIP, const USHORT port)
{
    if (pServerIP == nullptr) return;

    cNetAddress_.SetAddrInfor(pServerIP, port);

    for (uint32_t i = 0; i < WORKER_THREAD_COUNT; ++i)
    {
        vecWorkerThread_.emplace_back(std::make_unique<CSnowThread>(&CSnowServer::ExcuteWorkerThread, this));
    }

}

uint32_t CSnowServer::ExcuteWorkerThread()
{
    bool isRunning = true;

    SOCKET arrSocketEvent[WSA_MAXIMUM_WAIT_EVENTS];
    ZeroMemory(arrSocketEvent, WSA_MAXIMUM_WAIT_EVENTS);

    WSAEVENT arrIoEvent[WSA_MAXIMUM_WAIT_EVENTS];
    ZeroMemory(arrIoEvent, WSA_MAXIMUM_WAIT_EVENTS);


    WSAEVENT hIoEvent = WSACreateEvent();

    CSnowSocket listnSocket(SOCKET_TYPE::TCP_TYPE);

    listnSocket.OnBind(cNetAddress_.GetAddrInfor());
    listnSocket.OnListen();

    arrSocketEvent[0] = listnSocket.GetSocket();
    arrIoEvent[0]     = hIoEvent;

    // Listn Accpet는 메인스레드에서 처리하고
    // 나머지는 워커스레드에서 처리하고 virtual로 Post 처리를 하게 하자



    while (isRunning)
    {

        DWORD index = WSAWaitForMultipleEvents(0, arrIoEvent, FALSE, WSA_INFINITE, FALSE);






    }
    return 0;
}

