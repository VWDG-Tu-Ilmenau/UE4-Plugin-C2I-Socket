// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "C2I_Socket.h"
#include "C2I_SocketBPLibrary.h"
#include "C2I_SingletonSocket.h"

UC2I_SocketBPLibrary::UC2I_SocketBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

// float UC2I_SocketBPLibrary::C2I_SocketSampleFunction(float Param)
// {
// 	return -1;
// }


bool UC2I_SocketBPLibrary::bIsOn = true;

void UC2I_SocketBPLibrary::C2I_Connect()
{
	C2I_SingletonSocket::GetInstance().Connect();
	bIsOn = true;
}

void UC2I_SocketBPLibrary::C2I_Send(FString _val)
{
	if (bIsOn)
		C2I_SingletonSocket::GetInstance().Send(_val);
}

void UC2I_SocketBPLibrary::C2I_Quit()
{
	C2I_SingletonSocket::GetInstance().QuitMe();
	bIsOn = false;
}

void UC2I_SocketBPLibrary::C2I_StopSending()
{
	C2I_SingletonSocket::GetInstance().StopSending();
}

void UC2I_SocketBPLibrary::C2I_ListenForConnection()
{
	C2I_SingletonSocket::GetInstance().ListenForConnection();
	bIsOn = true;

}
