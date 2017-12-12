// Fill out your copyright notice in the Description page of Project Settings.

#include "GPBHandler.h"


GPBHandler::GPBHandler()
{
}

GPBHandler::~GPBHandler()
{
}


std::string GPBHandler::GetGPBString(FString _targetComponent, FString _targetCommand, FString _evName, int32 _val, bool _isDebug)
{
	std::string res = "";

	//////////////////////////////////////////////////////////////////////////
	//prepare GPB
	c2ipb::Call datapacket;

	datapacket.set_targetcomponent(TCHAR_TO_UTF8(*_targetComponent));
	datapacket.set_targetcommand(TCHAR_TO_UTF8(*_targetCommand));
	c2ipb::Call_Event* datapacketevent = datapacket.mutable_event();

	datapacketevent->set_eventname(TCHAR_TO_UTF8(*_evName));
	datapacketevent->set_eventtype(c2ipb::Call_Event_EventType_TYPEINT);
	datapacketevent->set_val_int(_val);

	if (_isDebug)
	{
		res = datapacket.DebugString();
	}
	else
	{
		datapacket.SerializeToString(&res);
	}

	return res;
}

std::string GPBHandler::GetGPBString(FString _targetComponent, FString _targetCommand, FString _evName, float _val, bool _isDebug)
{
	std::string res = "";

	//////////////////////////////////////////////////////////////////////////
	//prepare GPB
	c2ipb::Call datapacket;

	datapacket.set_targetcomponent(TCHAR_TO_UTF8(*_targetComponent));
	datapacket.set_targetcommand(TCHAR_TO_UTF8(*_targetCommand));
	c2ipb::Call_Event* datapacketevent = datapacket.mutable_event();

	datapacketevent->set_eventname(TCHAR_TO_UTF8(*_evName));
	datapacketevent->set_eventtype(c2ipb::Call_Event_EventType_TYPEINT);
	datapacketevent->set_val_float(_val);

	if (_isDebug)
	{
		res = datapacket.DebugString();
	}
	else
	{
		datapacket.SerializeToString(&res);
	}

	return res;
}

std::string GPBHandler::GetGPBString(FString _targetComponent, FString _targetCommand, FString _evName, FString _val, bool _isDebug)
{
	std::string res = "";

	//////////////////////////////////////////////////////////////////////////
	//prepare GPB
	c2ipb::Call datapacket;

	datapacket.set_targetcomponent(TCHAR_TO_UTF8(*_targetComponent));
	datapacket.set_targetcommand(TCHAR_TO_UTF8(*_targetCommand));
	c2ipb::Call_Event* datapacketevent = datapacket.mutable_event();

	datapacketevent->set_eventname(TCHAR_TO_UTF8(*_evName));
	datapacketevent->set_eventtype(c2ipb::Call_Event_EventType_TYPEINT);
	datapacketevent->set_val_string(TCHAR_TO_UTF8(*_val));

	if (_isDebug)
	{
		res = datapacket.DebugString();
	}
	else
	{
		datapacket.SerializeToString(&res);
	}

	return res;
}

