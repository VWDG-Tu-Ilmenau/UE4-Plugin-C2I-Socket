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
		void ListenForConnection();

		//Listens for connection without spawning a thread
		void SetupSocketServer();

		//Sends a string via an established socket connection
		void Send(FString _val);

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


	};



}
