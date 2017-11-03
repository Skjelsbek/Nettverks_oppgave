#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <sstream>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

void updateCSV(char *buff, int len) 
{
	try 
	{
		time_t now;
		struct tm nowLocal;
		now = time(0);
		localtime_s(&nowLocal, &now);
		
		std::ostringstream oss;
		buff[len - 1] = '\0';
		oss << nowLocal.tm_mday << "." << nowLocal.tm_mon + 1 << "." << nowLocal.tm_year + 1900 << ", ";
		oss << nowLocal.tm_hour << ":" << nowLocal.tm_min << ", ";
		oss << buff;
	
		std::fstream file;
		file.open("log.csv", std::ios::out | std::ios::app);
	
		file.seekg(0, file.end);
		size_t len = file.tellg();	
		if (len == 0)
		{
			file << "Date, Time, Temp, Hum\n";
		}

		file << oss.str();

		std::cout << "Log updated!" << std::endl;
	}
	catch (std::fstream::failure e)
	{
		std::cout << "Error updating log!" << std::endl;
	}
}

int main()
{			
	// Initialize Winsock	
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
		return 1;
	}

	// Create a socket for sending data
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}
	
	// Set up the server structure with the IP address of the server
	// and the specified port number.
	std::string ipAddr = "192.168.1.2";
	unsigned short port = 27015;
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, ipAddr.c_str(), &server.sin_addr);

	// Connecting to server
	iResult = connect(sock, (sockaddr*)&server, sizeof(server));
	if (iResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server, error: " << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	// Variables for sending and receiving data
	char buffer[1024];
	int bufLen = 1024;
	std::string userInput;

	// bool to handle disconnect
	bool dcRequest = false;

	
	// Sending user input, and receiving response from server
	do
	{
		// User input prompt
		std::cout << ">";
		getline(std::cin, userInput);
		
		if (userInput.size() > 0)
		{
			// Sending user input
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);

			/*
			 * Check the return value of send function to see if the transfer was successful.
			 * If the transfer was successful and the user didn't send disconnect request,
			 * recive response from server.
			 */			
			if (sendResult != SOCKET_ERROR && userInput != "disconnect")
			{
				// Clear buffer and receive response from server
				ZeroMemory(buffer, bufLen);
				int bytesReceived;
				bytesReceived = recv(sock, buffer, bufLen, 0);

				// Print response if something was received
				if (bytesReceived > 0 && userInput != "update")
				{
					std::cout << "Server>" << std::string(buffer, 0, bytesReceived) << std::endl;					
				}
				else if (userInput == "update")
				{
					updateCSV(buffer, bytesReceived);
				}
			}
			else if (userInput == "disconnect")
			{
				// If the user sent disconnect request, set dcRequest true to close connection to server
				dcRequest = true;
			}			
		}		
	} while (!dcRequest);
	
	// Clean up and quit.
	std::cout << "Exiting" << std::endl;
	closesocket(sock);
	WSACleanup();
	return 0;
}