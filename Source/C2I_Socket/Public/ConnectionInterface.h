#pragma once



#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Sockets/Public/Sockets.h"

#include "Runtime/Core/Public/HAL/RunnableThread.h"


/************************************************************************/
/* Creates a TCP Server                                                 */
/************************************************************************/

namespace C2I_Socket
{

	class ConnectionInterface : public FRunnable
	{
	public:

		static ConnectionInterface* Runnable;
		FRunnableThread* Thread;

		ConnectionInterface();
		~ConnectionInterface();

		virtual uint32 Run() override;
		//Spawns a thread and listens for connections
		void ListenForConnection(FString _ip, int32 _port);

		//Listens for connection without spawning a thread
		void SetupSocketServer();

		//Sends a string via an established socket connection
		void Send(FString _val);

		void Send(float _val);

		//Closes sockets, and stops sending with a flag.
		void QuitMe();

		//Stops sending with a flag.
		void StopSending();

	private:
		FSocket* Socket = NULL;
		FSocket* FinalSocket = NULL;

		bool bIsConnected = false;

		FCriticalSection MyMutex;
		bool bIsSend;

		void SetIP(FString _ip);
		void SetPort(int32 _port);

		FString IP = "127.0.0.1";
		int32 Port = 12345;

	};



}
