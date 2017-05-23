#pragma once
#include "ConnectionInterface.h"


namespace C2I_Socket 
{
	class C2I_SingletonSocket
	{
	public:

		static C2I_SingletonSocket& GetInstance() {
			static C2I_SingletonSocket instance;
			return instance;
		}
		C2I_SingletonSocket(C2I_SingletonSocket const&) = delete;
		void operator=(C2I_SingletonSocket const&) = delete;


		//DEPRECATED, please use ListenForConnection in production setting.
		void Connect();

		//Sends a String via an established socket connection.
		void Send(FString _val);

		//Sends a String via an established socket connection.
		void Send(float _val);

		//Stops sending with a bool flag.
		void StopSending();

		//Spawns a thread and waits for a client connection.
		void ListenForConnection(FString _ip, int32 _port);

	private:
		C2I_SingletonSocket();
		ConnectionInterface* connectionInterface;


	public:
		void QuitMe();

	};

}