#include "Client.h"

Client::Client()
{	
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); // Initialize Winsock	

	if (iResult != NO_ERROR) {
		// If something goes wrong initializing winsock, throw exception with error message
		std::ostringstream oss;
		oss << "WSAStartup failed with error: " << iResult << std::endl;
		throw std::exception(oss.str().c_str());
	}
	
	sock = socket(AF_INET, SOCK_STREAM, 0); // Create a socket for sending/receiving data

	if (sock == INVALID_SOCKET) {
		// If something goes wrong creating socket, throw exception with error message
		std::ostringstream oss;
		oss << "Socket failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		throw std::exception(oss.str().c_str());
	}

	std::cout << "Socket created!\n";

	addFuncPointers(); // Adding function pointer to the hash map
}


Client::~Client()
{
	// Clean up and quit.
	std::cout << "Exiting\n";
	closesocket(sock);
	WSACleanup();
}

void Client::serverInit(const std::string &ip, const unsigned int &port)
{
	// Set up the server structure with the IP address of the server
	// and the specified port number.
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &server.sin_addr);

	std::cout << "Server initialized!\n";
}

void Client::serverConnect()
{	
	int iResult = connect(sock, (sockaddr*)&server, sizeof(server)); // Connecting to server

	if (iResult == SOCKET_ERROR)
	{
		// If something goes wrong connecting to server, throw exception with error message
		std::ostringstream oss;
		oss << "Can't connect to server, error: " << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		throw std::exception(oss.str().c_str());
	}

	std::cout << "Connected to server!\n";
}

void Client::addFuncPointers()
{
	// Adding methods with corresponding key to map
	map.append("csv", &Client::update);
	map.append("day", &Client::updateDay);
	map.append("hour", &Client::updateHour);
	map.append("min", &Client::updateMin);
	map.append("sec", &Client::updateSec);
	map.append("stop", &Client::stopUpdate);
	map.append("disconnect", &Client::dc);
	map.setDefault(&Client::sendAndReceive);
}

void Client::promptUser()
{
	// User input prompt
	getline(std::cin, userInput);
	if (userInput.size() > 0)
	{
		// If the user typed something, grap the corresponding function from map, run in a thread.				
		std::thread t1((this->map.get(userInput)), this);
		t1.detach(); // Detach the thread so we're still able to operate the main thread
	}
}

void Client::sendAndReceive()
{	
	int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0); // Sending user input

	/*
	* Check the return value of send function to see if the transfer was successful.
	* If the transfer was successful recive response from server.
	*/
	if (sendResult != SOCKET_ERROR)
	{
		// Clear buffer and receive response from server
		ZeroMemory(buffer, bufLen);
		bytesReceived = recv(sock, buffer, bufLen, 0);
		
		if (userInput != "csv")
		{
			// Print response if something was received
			std::stringstream stream;
			stream << "Server>" << std::string(buffer, 0, bytesReceived) << std::endl;
			std::cout << stream.str();
		}
	}	
}

void Client::update()
{
	// Set userInput to "csv" so that the sendAndReceive method sends "csv", and server then returns
	// the data to put in the csv.
	userInput = "csv";
	sendAndReceive();
	updateCSV();

}

struct tm Client::getCurrentTime()
{
	// Getting current time
	time_t now;
	struct tm nowLocal;
	now = time(0);
	localtime_s(&nowLocal, &now);

	return nowLocal;
}

void Client::updateCSV()
{
	// Since editing the file may go wrong, we wrap it in a try-catch block
	try
	{		
		// Open file log.csv
		std::fstream file;
		file.open("log.csv", std::ios::out | std::ios::app);		

		// Append date and time to output string stream
		struct tm currentTime = getCurrentTime();
		std::ostringstream oss;
		buffer[bytesReceived] = '\0';
		oss << std::setfill('0') << std::setw(2) << currentTime.tm_mday << "." << std::setfill('0') << std::setw(2) << currentTime.tm_mon + 1 << "." << currentTime.tm_year + 1900 << ", ";
		oss << std::setfill('0') << std::setw(2) << currentTime.tm_hour << ":" << std::setfill('0') << std::setw(2) << currentTime.tm_min << ", ";
		oss << buffer << std::endl;

		// Find length of file
		file.seekg(0, file.end);
		size_t len = (size_t)file.tellg();

		if (len == 0)
		{
			// Append headers when there is nothing else in the csv
			file << "Date, Time, Temp, Hum\n";
		}

		file << oss.str(); // Append the output string stream to the file
		
		std::cout << "Log updated!\n";
	}
	catch (std::fstream::failure e)
	{
		// Printing error message if something went wrong writing to file		
		std::cout << "Error updating log!\n";
	}
}

void Client::updateDay()
{	
	runUpdateLoop = true; // False by default, need to set true

	while (runUpdateLoop)
	{		
		// While runUpdateLoop is true, update csv every 24 hours
		update();
		std::this_thread::sleep_for(std::chrono::hours(24));
	}		
}

void Client::updateHour()
{
	runUpdateLoop = true;

	while (runUpdateLoop)
	{
		// While runUpdateLoop is true, update csv every hour
		update();
		std::this_thread::sleep_for(std::chrono::hours(1));
	}
}

void Client::updateMin()
{	
	runUpdateLoop = true;

	while (runUpdateLoop)
	{
		// While runUpdateLoop is true, update csv every minute
		update();
		std::this_thread::sleep_for(std::chrono::minutes(1));
	}
}

// Used for testing purposes
void Client::updateSec()
{
	runUpdateLoop = true;

	while (runUpdateLoop)
	{
		// While runUpdateLoop is true, update csv every 5 seconds
		update();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void Client::stopUpdate()
{
	runUpdateLoop = false; // Sets runUpdateLoop false to stop threads
}

void Client::dc()
{
	// Sends disconnect request to server, and sets dcRequest true so we break out of the main loop
	sendAndReceive();
	dcRequest = true;
}