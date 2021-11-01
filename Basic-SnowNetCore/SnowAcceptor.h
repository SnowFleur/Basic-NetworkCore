#pragma once
/*
- Developer: PDH
- Descriptor: Blocking Acceptor ������ �����ϴ� �߻� Class
*/

#include"SnowThread.h"
#include"SnowSocket.h"

class CSnowAcceptor : public CSnowThread
{
private:
    CSnowSocket       listenSocket_;
    bool              isRunning_;
    HANDLE            accpetStart_;
public:
    CSnowAcceptor() :
        CSnowThread(&CSnowAcceptor::OnAccept, this)
        , listenSocket_(SOCKET_TYPE::TCP_TYPE)
        , isRunning_(false)
        , accpetStart_(INVALID_HANDLE_VALUE)
    {}

    ~CSnowAcceptor()override
    {
        listenSocket_.Close();
        isRunning_ = false;
    }

public:
    inline void SetIsRunning(const bool flag)   { isRunning_ = false; }
    inline bool GetIsRunning()const             { return isRunning_; }

    void StartAcceptr() 
    {

    }

    uint32_t OnAccept()
    {

        while (isRunning_)
        {


        }
    }

    virtual void PostAccpet() = 0;
};

