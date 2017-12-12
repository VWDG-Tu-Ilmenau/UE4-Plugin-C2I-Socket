// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AllowWindowsPlatformTypes.h"
#include "MessageC2I_to_Dispatcher.pb.h"
#include "HideWindowsPlatformTypes.h"

/**
 * 
 */
class GPBHandler
{
public:

	std::string GetGPBString(FString _targetComponent, FString _targetCommand, FString _evName, int32 _val, bool _isDebug);
	std::string GetGPBString(FString _targetComponent, FString _targetCommand, FString _evName, float _val, bool _isDebug);
	std::string GetGPBString(FString _targetComponent, FString _targetCommand, FString _evName, FString _val, bool _isDebug);


	GPBHandler();

	~GPBHandler();
};
