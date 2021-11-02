#pragma once
/*
- Developer: PDH
- Descriptor: Blocking Acceptor 역할을 수행하는 추상 Class
- 추가 옵션은 상속받은 클래스가 알아서 추가한다. 여기서 당연하게도 기본적인것만
*/

#include"SnowThread.h"
#include"SnowSocket.h"
#include"NetAddress.h"

class CSnowAcceptor : public CSnowThread
{
private:
    CSnowSocket       cListenSocket_;
    CNetAddress       cServerAddress_;
    bool              isRunning_;
    HANDLE            hAcceptStart_;
public:
    CSnowAcceptor(const char* serverAddr, USHORT port) :
        CSnowThread(&CSnowAcceptor::OnAccept, this)
        , cListenSocket_(SOCKET_TYPE::TCP_TYPE)
        , isRunning_(false)
        , hAcceptStart_(INVALID_HANDLE_VALUE)
    {
        cServerAddress_.SetAddrInfor(serverAddr, port);
        hAcceptStart_ = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    ~CSnowAcceptor()override
    {
        CloseHandle(hAcceptStart_);
        cListenSocket_.OnClose();
        isRunning_ = false;
    }

public:
    inline void SetIsRunning(const bool flag)   { isRunning_ = false; }
    inline bool GetIsRunning()const             { return isRunning_; }

    void StartAcceptr() 
    {
        SetEvent(hAcceptStart_);
    }

    uint32_t OnAccept()
    {
        WaitForSingleObject(hAcceptStart_, INFINITE);

        if (cListenSocket_.OnBind(reinterpret_cast<SOCKADDR_IN*>(cServerAddress_.GetAddrInfor())) == false) return;
        if (cListenSocket_.OnListen() == false) return;

        CNetAddress clinetAddress;
        SOCKET tempSocket_;
        while (isRunning_)
        {

            tempSocket_ = INVALID_SOCKET;

            ZeroMemory(&clinetAddress, sizeof(CNetAddress));
            int addrLen = sizeof(SOCKADDR);

            tempSocket_ = cListenSocket_.OnAccept(reinterpret_cast<SOCKADDR*>(clinetAddress.GetAddrInfor()));

            if (tempSocket_ == INVALID_SOCKET)
            {
                PRINT_ERROR_LOG("Accpeted Socket is INVALID_SOCKET: ", WSAGetLastError(), "\n");
            }
            else
            {
                clinetAddress.PrintIPAndPort();
                CSnowSocket hTempSocket(SOCKET_TYPE::TCP_TYPE);
                hTempSocket.SetSocket(tempSocket_);
                PostAccpet(std::move(hTempSocket));
            }
        }
    }

    virtual void PostAccpet(CSnowSocket&& acceptedSocket) = 0;
};

