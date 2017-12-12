#include "ConnectionInterface.h"

#include "C2I_Socket.h"


#include "Runtime/Sockets/Public/SocketSubsystem.h"

#include <string>
#include <iostream>


using namespace C2I_Socket;


ConnectionInterface* ConnectionInterface::Runnable = NULL;

ConnectionInterface::ConnectionInterface()
{
	bIsConnected = false;
	bIsSend = true;
	FinalSocket = NULL;
	Socket = NULL;
}


ConnectionInterface::~ConnectionInterface()
{

}

uint32 ConnectionInterface::Run()
{
	UE_LOG(LogTemp, Log, TEXT("Run"));

	SetupSocketServer();
	return 3791;
}

void C2I_Socket::ConnectionInterface::ListenForConnection(FString _ip, int32 _port)
{
	UE_LOG(LogTemp, Log, TEXT("ListenForConnection"));
	
	SetIP(_ip);
	SetPort(_port);

	Thread = FRunnableThread::Create(this, TEXT("Test")); //windows default = 8mb for thread, could specify more
//	Runnable = new ConnectionInterface();

}

void ConnectionInterface::SetupSocketServer()
{
	if (bIsConnected)
		return;

	bIsConnected = false;
	bIsSend = false;

	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FString address = IP;
	int32 port = Port;

	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	Socket->SetReuseAddr(true);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	bool bind = Socket->Bind(*addr);

	if (bind)
	{
		UE_LOG(LogTemp, Log, TEXT("Socket bound."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Socket not bound.1"));	
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetSocketError();
		return;
	}

	bool listen = Socket->Listen(port);

	if (listen)
	{
		UE_LOG(LogTemp, Log, TEXT("Socket listens."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Socket not listening."));
		return;
	}


	FinalSocket = Socket->Accept(*addr, TEXT("default"));
	bIsConnected = true;
	bIsSend = true;
}

void ConnectionInterface::Send(FString _val)
{
	if (MyMutex.TryLock())
	{
		FString serialized = _val;
		TCHAR *serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		bool successful = false;
		if (FinalSocket && Socket && bIsSend && bIsConnected)
		{
			successful = FinalSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);

		}
		MyMutex.Unlock();
	}

}

void C2I_Socket::ConnectionInterface::Send(float _val)
{
	if (MyMutex.TryLock())
	{

		
		FString serialized = FString::SanitizeFloat(_val);
		TCHAR *serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		bool successful = false;
		if (FinalSocket && Socket && bIsSend && bIsConnected)
		{
			successful = FinalSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);

		}

		MyMutex.Unlock();
	}
}

//untested!
void C2I_Socket::ConnectionInterface::Send(int32 _val)
{
	if (MyMutex.TryLock())
	{
		FString serialized = FString::FromInt(_val);
		TCHAR *serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		bool successful = false;
		if (FinalSocket && Socket && bIsSend && bIsConnected)
		{
			successful = FinalSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);

		}
		MyMutex.Unlock();
	}
}


void C2I_Socket::ConnectionInterface::SendAsGPB(int32 _val, FString _targetComponent, FString _targetCommand, FString _evName, bool _isDebug)
{
	if (MyMutex.TryLock())
	{
		
		//////////////////////////////////////////////////////////////////////////
		//Get final string
		
		std::string res= Gpbhandler_.GetGPBString(_targetComponent, _targetCommand, _evName, _val, _isDebug);

		SendGPB(res);

		MyMutex.Unlock();
	}
}

void C2I_Socket::ConnectionInterface::SendAsGPB(float _val, FString  _targetComponent, FString _targetCommand, FString _evName, bool _isDebug)
{
	if (MyMutex.TryLock())
	{
		std::string res = Gpbhandler_.GetGPBString(_targetComponent, _targetCommand, _evName, _val, _isDebug);

		SendGPB(res);

		MyMutex.Unlock();
	}
}

void C2I_Socket::ConnectionInterface::SendAsGPB(FString _val, FString  _targetComponent, FString _targetCommand, FString _evName, bool _isDebug)
{
	if (MyMutex.TryLock())
	{
		std::string res = Gpbhandler_.GetGPBString(_targetComponent, _targetCommand, _evName, _val, _isDebug);

		SendGPB(res);

		MyMutex.Unlock();
	}
}


//////////////////////////////////////////////////////////////////////////

void C2I_Socket::ConnectionInterface::SendGPB(std::string res)
{
	//////////////////////////////////////////////////////////////////////////
	//prepare payload size
	int32 sizePayload = res.length();
	uint8_t* sizeOfPayloadInBytes = (uint8_t*)&sizePayload;

	//////////////////////////////////////////////////////////////////////////
	//send size
	int32 sentSize = 0;
	bool successfulSize = false;
	if (FinalSocket && Socket && bIsSend && bIsConnected)
	{
		successfulSize = FinalSocket->Send(sizeOfPayloadInBytes, sizeof(int32), sentSize);
	}
	if (!successfulSize)
	{
		UE_LOG(LogTemp, Log, TEXT("Sending size: unsuccesful."));
	}
	if (sentSize != sizeof(int32))
	{
		UE_LOG(LogTemp, Log, TEXT("Sending Size size: bytes send != bytes size."));
	}

	//////////////////////////////////////////////////////////////////////////
	//send payload
	int32 sentPayload = 0;
	bool successfulPayload = false;
	if (FinalSocket && Socket && bIsSend && bIsConnected)
	{
		successfulPayload = FinalSocket->Send((uint8_t*)res.c_str(), sizePayload, sentPayload);
	}
	if (!successfulPayload)
	{
		UE_LOG(LogTemp, Log, TEXT("Sending payload: unsuccesful."));
	}
	if (sentPayload != sizeof(int32))
	{
		UE_LOG(LogTemp, Log, TEXT("Sending payload size: bytes send != bytes size."));
	}
}

void ConnectionInterface::QuitMe()
{
	MyMutex.Lock();
	bIsConnected = false;
	StopSending();

	FPlatformProcess::Sleep(1);
	if (FinalSocket)
	{
		if (!FinalSocket->Close())
			UE_LOG(LogTemp, Log, TEXT("FinalSocket not closed."));
	}

	if (Socket)
	{
		if (!Socket->Close())
			UE_LOG(LogTemp, Log, TEXT("Socket not closed."));
	}

	UE_LOG(LogTemp, Log, TEXT("All Sockets closed."));


	MyMutex.Unlock();

}

void ConnectionInterface::StopSending()
{
	bIsSend = false;
}


void ConnectionInterface::SetIP(FString _ip)
{
	IP = _ip;
}

void ConnectionInterface::SetPort(int32 _port)
{
	Port = _port;
}