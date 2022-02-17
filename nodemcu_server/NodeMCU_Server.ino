#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

int led = 5; // the pin the LED is connected to

const char* ssid = "WE5B3FED";                  // Your wifi Name       
const char* password = "k9386044"; // Your wifi Password
const char* Commands_Reply;                 // The command variable that is sent to the client

//const char * host = "192.168.1.18";          // IP Client

WiFiServer server(7777);

void setup() {
  // put your setup code here, to run once:
 // pinMode(led, OUTPUT);                     // Declare the LED as an output
  Serial.begin(115200);                     // initialize serial:
  delay(10);

  Serial.println("");
  Serial.println("Server-------------------------------");
  Serial.print("Configuring access point");
  WiFi.begin(ssid, password);

  // Waiting to connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    Serial.println("");
    Serial.println("WiFi connected");

  // Start the server
    server.begin();
    Serial.println("Server started");

  // Print the IP address
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
    Serial.println("-------------------------------------");
    Serial.println("");
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    
    while(client.connected()){      
      while(client.available()>0){
        // read data from the connected client
        Serial.write(client.read() + "\n"); 
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        client.write(Serial.read());
      }
    }
    client.stop();
    Serial.println("Client disconnected");    
  }
}
