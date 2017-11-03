#include <SPI.h>
#include <UIPEthernet.h> // Identical with Ethernet.h, but works with the module
#include "dht.h"  // Temp and humidity sensor lib

// Defining temp and humidity sensor
#define sensor A0
dht DHT;

char *myBuffer; // Buffer with caracters to send to client

// Variables to compare and decide what to print to client
char *readTemp;
int tempSize;
char *readHum;
int humSize;
char *discon;
int disconSize;
int index;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 2);
IPAddress myDns(192,168,1, 0);
IPAddress gateway(192, 168, 1, 0);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(23);
boolean alreadyConnected = false; // whether or not the client was connected previously

/* 
 * Compare two arrays where size of arr1 is less than size of arr2
 * so that we can compare a preset array to whats in the buffer.
 * This is used to decide which function to use for returning to client
 */
bool compArray(char* arr1, unsigned int size1, char* arr2){
  for (unsigned int i = 0; i < size1; i++){
    if (arr1[i] != arr2[i]){
      return false;
    }
  }
  return true;
}

// Returns the number of digits of a number.
// This is used to split a number into digits in a char array for sending purposes.
int intSize(int _int){
  int size = 0;
  int i = 0;
  while (_int > 0){
    _int /= 10;
    size++;
  }
 
  return size;
}

// Converts an integer to a char array
char *toStr(int _int, int _size){  
  char *str = new char[_size];
  for (int i = 0; i < _size; i++)
  {
    str[_size - i - 1] = (_int % 10) + 48; // Need to add 48 to the digit so we get the ascii value of it
    _int /= 10;
  }
  return str;
}

// Sends an integer value to the client
void sendValue(int num) {
  // Getting the size of the number and convert it to a char array
  int _size = intSize(num);
  char *value = toStr(num, _size);

  // Send each digit of the number to the client (and serial monitor for testing purposes)
  for (int i = 0; i < _size; i++) {
    server.write(value[i]);
    Serial.println(value[i]);
  }
  
  // Send a new line and carriage return
  server.write('\n');
  server.write('\r');
  
  delete[] value; // What's in value is stored on heap, we must delete the pointer to stop memory leaks
}

// Sends an error message to the client
void errorMessage() {
  char *message = new char[65];
  message = "Type check_temp to get temperature, or check_hum to get humidity!";

  for (int i = 0; i < 65; i++) {
    server.write(message[i]);
  }
  server.write('\n');
  server.write('\r');

  delete[] message;
}

// Clears the input buffer and resets index variable
void clearBuffer() {
  for (int i = 0; i < 100; i++) {
    myBuffer[i] = 0;
  }
  index = 0;
}

void setup() {
  // initialize the ethernet device
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  // start listening for clients
  server.begin();
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Prints the ip address to Serial monitor
  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());

  // Instantiate buffer
  myBuffer = new char[100];  
  index = 0; 

  // Instantiate readTemp
  tempSize = 10;
  readTemp = new char[tempSize];
  readTemp= "check_temp";

  // Instantiate readHum
  humSize = 9;
  readHum = new char[humSize];
  readHum= "check_hum";

  // Instantiate discon
  disconSize = 10;
  discon = new char[disconSize];
  discon = "disconnect";
}

void loop() {
  // Wait for a new client
  EthernetClient client = server.available();

  // When the client sends the first byte, say hello
  if (client) {
    if (!alreadyConnected) {      
      client.flush(); // Clear the input buffer
      Serial.println("We have a new client");
      client.println("Hello, client!");
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      // read the bytes incoming from the client
      myBuffer[index++] = client.read();    
    }
    
    if (index > 0 && myBuffer[index - 1] == '\r') {
      if (compArray(readTemp, tempSize, myBuffer) == true) {
        // Sends temperature to client
        DHT.read11(sensor);
        int temp = (int)DHT.temperature;
        sendValue(temp);
      } else if (compArray(readHum, humSize, myBuffer) == true) {
        // Sends humidity to client
        DHT.read11(sensor);
        int hum = (int)DHT.humidity;
        sendValue(hum);
      } else if (compArray(discon, disconSize, myBuffer) == true) {
        // If client sends dsiconnect, stop the communication
        alreadyConnected = false;
        client.stop();
      } else {     
        // If the user didn't type any of the above commands, send error message 
        errorMessage();
      }

      // Clear input buffer
      client.flush();
      clearBuffer();
    }
  }
}
