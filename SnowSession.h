#pragma once

#include"WindowsHeader.h"
#include"DataTypes.h"
#include"SnowSocket.h"
#include"Buffer.h"
#include<queue>

class CSnowSession{
	//To do Std::any
    typedef void* Packet;

private:
	
	CSnowSocket				socket_;
	//CNetAddress			sessionAddress_;
	SessionID				sessionId_;
	CBuffer					sendBuffer_;
	CBuffer					recvBuffer_;

	std::atomic<bool>		sendComplete_;
	std::queue<Packet>		sendQueue_;

private:
	bool PacketValidCheck(const char* packet);
public:

	CSnowSession& operator=(const CSnowSession&)	= delete;
	CSnowSession& operator=(CSnowSession&&)			= delete;
	CSnowSession(const CSnowSession&)				= delete;
	CSnowSession(CSnowSession&&)					= delete;

    CSnowSession(const SOCKET_TYPE socketType, const SessionID sessionID, const uint32_t BUFFER_SIZE);
	virtual ~CSnowSession()noexcept;
public:

public:

	/*Get Function*/
	inline SessionID		GetSessionID()const { return sessionId_; }
	
	/*Set Function*/
	inline void				SetSessionID(const SessionID sessionId) { sessionId_ = sessionId; }

	bool			OnRecv();
	virtual void	PostRecv() = 0;

	bool			OnSend(void* packet);
	virtual void	PostSend() = 0;

	void    PostSend(void* packet, DWORD ioByte);
	void    PushSendQueue(void* packet);
};

























