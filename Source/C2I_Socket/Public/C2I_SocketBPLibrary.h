// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "C2I_SocketBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UC2I_SocketBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "C2I_Socket sample test testing"), Category = "C2I_SocketTesting")
	//static float C2I_SocketSampleFunction(float Param);

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "C2I_Socket sample test testing"), Category = "C2I_SocketTesting")
		//static float C2I_SocketSampleFunction(float Param);

	/************************************************************************/
	/* Send as value                                                        */
	/************************************************************************/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SendViaC2ISocketString", Keywords = "C2I_Socket send socket string"), Category = "C2I")
		static void C2I_SendString(FString _val);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SendViaC2ISocketFloat", Keywords = "C2I_Socket send socket float"), Category = "C2I")
		static void C2I_SendFloat(float _val);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SendViaC2ISocketInt", Keywords = "C2I_Socket send socket int"), Category = "C2I")
		static void C2I_SendInt(int32 _val);


	/************************************************************************/
	/* Send as GPB                                                          */
	/************************************************************************/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SendViaC2ISocketStringAsGPB", Keywords = "C2I_Socket send socket string GPB"), Category = "C2I")
		static void C2I_SendStringAsGPB(FString _val);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SendViaC2ISocketFloatAsGPB", Keywords = "C2I_Socket send socket float GPB"), Category = "C2I")
		static void C2I_SendFloatAsGPB(float _val);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SendViaC2ISocketIntAsGPB", Keywords = "C2I_Socket send socket int GPB"), Category = "C2I")
		static void C2I_SendIntAsGPB(int32 _val);

	/************************************************************************/
	/* Management methods                                                   */
	/************************************************************************/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetC2ISocket", Keywords = "C2I_Socket get socket"), Category = "C2I")
		static void C2I_Connect();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "QuitC2ISocket", Keywords = "C2I_Socket quit socket"), Category = "C2I Socket")
		static void C2I_Quit();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopSendingViaC2ISocket", Keywords = "C2I_Socket stop sending socket"), Category = "C2I")
		static void C2I_StopSending();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ListenForConnectionWithC2ISocket", Keywords = "C2I_Socket listen socket"), Category = "C2I")
		static void C2I_ListenForConnection(FString _ip = "127.0.0.1", int32 _port=12345);

private:

	static bool bIsOn;
};
