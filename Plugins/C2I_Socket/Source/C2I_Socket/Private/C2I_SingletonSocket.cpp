#include "C2I_Socket.h"

#include "C2I_SingletonSocket.h"

using namespace C2I_Socket;

C2I_SingletonSocket::C2I_SingletonSocket()
{
	UE_LOG(LogTemp, Log, TEXT("C2I_SingletonSocket created."));

}

void C2I_SingletonSocket::QuitMe()
{
	UE_LOG(LogTemp, Log, TEXT("C2I_SingletonSocket quit."));
	if (connectionInterface)
	{
		connectionInterface->StopSending();
		FPlatformProcess::Sleep(1);
		connectionInterface->QuitMe();
		delete connectionInterface;
	}
}

void C2I_SingletonSocket::Connect()
{
	UE_LOG(LogTemp, Log, TEXT("C2I_SingletonSocket connect."));
	connectionInterface = new ConnectionInterface();
	connectionInterface->SetupSocketServer();
}

void C2I_SingletonSocket::Send(FString _val)
{
	if (connectionInterface)
		connectionInterface->Send(_val);
}

void C2I_SingletonSocket::StopSending()
{
	
	if (connectionInterface)
		connectionInterface->StopSending();
	
}

void C2I_SingletonSocket::ListenForConnection()
{
	connectionInterface = new ConnectionInterface();
	connectionInterface->ListenForConnection();
}