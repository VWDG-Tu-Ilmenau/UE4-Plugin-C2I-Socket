#include "C2I_Socket.h"

#include "ConnectionInterface.h"

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

void ConnectionInterface::ListenForConnection()
{
	UE_LOG(LogTemp, Log, TEXT("ListenForConnection"));



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

	FString address = TEXT("127.0.0.1");
	int32 port = 12345;

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
