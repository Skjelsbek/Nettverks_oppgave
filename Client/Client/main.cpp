#include "Client.h"

int main()
{			
	// Try-catch block just in case something goes wrong during initialization of either winsoc, client or server.
	try
	{		
		Client *client = new Client(); // Creating a client object. Initializes winsoc and creates a socket in the constructor
		client->serverInit("192.168.1.2", 27015); // Initializes a server with ip and port
		client->serverConnect(); // Connect to server

		while (!client->dcRequest)
		{		
			// Prompt user to send a command, if user types "disconnect",
			// dcRequest is set to true and the program jumps out of the loop.
			client->promptUser();
		}

		delete client;
	}
	catch (const std::exception &e)
	{
		// Catches the thrown exceptions and prints what happend.
		// Returns 1 since we had an error.
		std::cout << e.what() << std::endl;
		system("pause");
		return 1;
	}				

	return 0;
}