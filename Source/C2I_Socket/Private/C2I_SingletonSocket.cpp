#include "C2I_SingletonSocket.h"
#include "C2I_Socket.h"



using namespace C2I_Socket;

C2I_SingletonSocket::C2I_SingletonSocket()
{

}

/************************************************************************/
/* Value                                                                */
/************************************************************************/

void C2I_SingletonSocket::Send(FString _val)
{
	if (connectionInterface)
		connectionInterface->Send(_val);
}

void C2I_SingletonSocket::Send(float _val)
{
	if (connectionInterface)
		connectionInterface->Send(_val);
}

void C2I_SingletonSocket::Send(int32 _val)
{
	if (connectionInterface)
		connectionInterface->Send(_val);
}


/************************************************************************/
/* GPB                                                                  */
/************************************************************************/
void C2I_SingletonSocket::SendAsGBP(float _val, FString _targetComponent, FString _targetCommand, FString _evName, bool _isDebug)
{
	if (connectionInterface)
		connectionInterface->SendAsGPB(_val, _targetComponent, _targetCommand, _evName, _isDebug);
}

void C2I_SingletonSocket::SendAsGBP(FString _val, FString _targetComponent, FString _targetCommand, FString _evName, bool _isDebug)
{
	if (connectionInterface)
		connectionInterface->SendAsGPB(_val, _targetComponent, _targetCommand, _evName, _isDebug);
}

void C2I_SingletonSocket::SendAsGBP(int32 _val, FString _targetComponent, FString _targetCommand, FString _evName, bool _isDebug)
{
	if (connectionInterface)
		connectionInterface->SendAsGPB(_val, _targetComponent, _targetCommand, _evName, _isDebug);
}

/************************************************************************/
/* Management                                                           */
/************************************************************************/

void C2I_SingletonSocket::StopSending()
{
	
	if (connectionInterface)
		connectionInterface->StopSending();
	
}

void C2I_Socket::C2I_SingletonSocket::ListenForConnection(FString _ip, int32 _port)
{
	connectionInterface = new ConnectionInterface();
	connectionInterface->ListenForConnection(_ip, _port);
}

void C2I_SingletonSocket::QuitMe()
{
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
	
	connectionInterface = new ConnectionInterface();
	connectionInterface->SetupSocketServer();
}