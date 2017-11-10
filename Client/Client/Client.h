#pragma once
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <sstream>
#include <iomanip>
#include "HashMap.h"
#include <thread>
#include <chrono>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

class Client
{
private:
	WSADATA wsaData; // Winsoc
	SOCKET sock; // Socket
	sockaddr_in server;	// Server

	// Variables for sending and receiving data
	std::string userInput;	
	char buffer[1024];
	int bufLen = 1024;
	int bytesReceived;
		
	bool runUpdateLoop; // Bool to cancel update loops
	
	HashMap<std::string, void(Client::*)(void)> map; // HashMap with function pointers
public:
	Client();
	~Client();
	void serverInit(const std::string & ip, const unsigned int & port);
	void serverConnect();
	void addFuncPointers();
	void promptUser();
	void sendAndReceive();
	void update();
	struct tm getCurrentTime();
	void updateCSV();
	void updateDay();
	void updateHour();
	void updateMin();
	void updateSec();
	void stopUpdate();
	void dc();

	// bool to handle disconnect
	// Public since used in main
	bool dcRequest = false;
};

