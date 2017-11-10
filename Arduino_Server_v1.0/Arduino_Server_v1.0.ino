#include <SPI.h>
#include <UIPEthernet.h> // Identical with Ethernet.h, but works with the module
#include "dht.h"  // Temp and humidity sensor lib
#include "LinkedList.h" // Homemade LinkedList lib

// Defining temp and humidity sensor
#define sensor A0
dht DHT;

char *_buffer; // Buffer with caracters to send to client

int index; // Current index in buffer (used when receiving)

LinkedList<String, void(*)(void)> list; // LinkedList with a String as "key" and pointer to a function as "value"

//Setting up unique MAC address for the arduino
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

//Setting static IP, DNS, GW and Subnet Mask
IPAddress ip(192, 168, 1, 2);
IPAddress myDns(192,168,1, 0);
IPAddress gateway(192, 168, 1, 0);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(27015); // Using "random" port above 1000 to not interfare with reserved ports

EthernetClient client; // Creating client object

boolean alreadyConnected = false; // Whether or not the client was connected previously

// Clears the input buffer and resets index variable
void clearBuffer() {
  client.flush();
  for (int i = 0; i < 1024; i++) {
    _buffer[i] = 0;
  }
  index = 0;
}

// Calculates number of digits in an integer
int ilen(int num) {
  int len = 0;
  while (num != 0) {
    num /= 10;
    len++;
  }
  return len;
}

// Integer to string function
String itos(int num){
  int len = ilen(num);
  char cArr[len + 1];
  for (unsigned int i = 0; i < len; i++)
  {
    cArr[len - i - 1] = (num % 10) + 48;
    num /= 10;
  }
  cArr[len] = '\0';
  String s = cArr;
  return s;
}

// Sends temperature to client
void sendTemp() {
  DHT.read11(sensor);
  int temp = (int)DHT.temperature;
  server.print(temp);
  Serial.println("Temperature sent!");
}

// Sends humidity to client
void sendHum(){     
  DHT.read11(sensor);
  int hum = (int)DHT.humidity;
  server.print(hum);
  Serial.println("Humidity sent!");
}

// Sends both temp and humidity to client.
// Used to update csv file.
void _update(){  
  DHT.read11(sensor);
  int temp = (int)DHT.temperature;
  int hum = (int)DHT.humidity;
  String s = itos(temp) + ", " + itos(hum);
  server.print(s);
  Serial.println("Update sent!");
}

// Disconnect client if disconnect request received.
void dc(){  
  alreadyConnected = false;
  client.stop();
  Serial.println("Client disconnected!");
  Serial.println();
}

void errorMsg() {
  server.print("Command not found!");
  Serial.println("Error message sent!");
}

void setup() {  
  Ethernet.begin(mac, ip, myDns, gateway, subnet); // initialize the ethernet device    
  server.begin(); // start listening for clients    
  Serial.begin(9600); // Open serial communications

  // Prints the ip address to Serial monitor
  Serial.print("Server address:");
  Serial.println(Ethernet.localIP());

  // Instantiate buffer
  _buffer = new char[1024];  
  index = 0; 

  // Appending pointers to functions with corresponding key to the linked list
  list.append("temp", sendTemp);
  list.append("hum", sendHum);
  list.append("csv", _update);
  list.append("disconnect", dc);
  list.setDefault(errorMsg);
}

void loop() {  
  client = server.available(); // Wait for a new client
  
  if (client) {
    // When the client sends the first byte, say hello
    if (!alreadyConnected) {      
      client.flush(); // Clear the input buffer
      Serial.println("We have a new client");
      server.print("Hello, client!");
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      // read the bytes incoming from the client to the buffer
      _buffer[index++] = client.read();      
      Serial.print(_buffer[index - 1]); 
    }
        
    if (index > 0 && _buffer[index - 1] == '\0') {
      Serial.println();
      String s = _buffer; // Convert buffer to String

      // Returns and runs the function corresponding to the command received.
      // If the received command doesn't appear as a key in the linked list,
      // it returns the default function printing error message.
      list.get(s)();    

      // Clear input buffers      
      clearBuffer();
    }
  }
}
