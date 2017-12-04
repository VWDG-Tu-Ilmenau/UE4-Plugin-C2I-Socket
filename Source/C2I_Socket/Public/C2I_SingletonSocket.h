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

		/************************************************************************/
		/* value                                                                */
		/************************************************************************/
		
		//Sends a String via an established socket connection.
		void Send(FString _val);

		//Sends a float via an established socket connection.
		void Send(float _val);

		//Sends a int64 via an established socket connection.
		void Send(int32 _val);

		/************************************************************************/
		/* GPB                                                                  */
		/************************************************************************/

		//Sends a float value packed in a GPB via an established socket connection
		void SendAsGBP(float _val); 

		//Sends a float value packed in a GPB via an established socket connection
		void SendAsGBP(FString _val);

		//Sends a float value packed in a GPB via an established socket connection
		void SendAsGBP(int32 _val);

		/************************************************************************/
		/* Management                                                           */
		/************************************************************************/

		//DEPRECATED, please use ListenForConnection in production setting.
		void Connect();
		
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