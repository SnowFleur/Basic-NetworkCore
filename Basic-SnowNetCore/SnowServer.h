#pragma once

#include<memory>
#include<vector>
#include"WindowsHeader.h"
#include"SnowSession.h"
#include"SnowThread.h"

using UptrSnowThread = std::unique_ptr<CSnowThread>;

class CSnowServer
{
private:
    const uint32_t                    WORKER_THREAD_COUNT;
    CNetAddress                       cNetAddress_;
    std::vector<UptrSnowThread>       vecWorkerThread_;
public:
    CSnowServer(const uint32_t workerThreadCount);
    ~CSnowServer()noexcept;

    CSnowServer(const CSnowServer&)                 = delete;
    CSnowServer& operator=(const CSnowServer&)      = delete;
    CSnowServer(CSnowServer&&)noexcept              = delete;
    CSnowServer& operator=(CSnowServer&&) noexcept  = delete;
public:

    void StartServer(const char* pServerIP, const USHORT port);
    uint32_t ExcuteWorkerThread();

    virtual void CompletedAccpet(CSnowSocket&& accpetCompleteSocket) = 0;
    virtual void CompletedSend(DWORD sendByte) = 0;
    virtual void CompletedRecv(DWORD recvByte) = 0;

};