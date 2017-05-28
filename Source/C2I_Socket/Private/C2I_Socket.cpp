// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "C2I_Socket.h"

#define LOCTEXT_NAMESPACE "FC2I_SocketModule"

void FC2I_SocketModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FC2I_SocketModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FC2I_SocketModule, C2I_Socket)