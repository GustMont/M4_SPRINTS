/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>


// Replace with your network credentials
const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output1State = "off";
String output2State = "off";
String output7State = "off";
String output8State = "off";
String output9State = "off";
String output37State = "off";

// Assign output variables to GPIO pins
const int output1 = 1;
const int output2 = 2;
const int output7 = 7;
const int output8 = 8;
const int output9 = 9;
const int output37 = 37;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output7, OUTPUT);
  pinMode(output8, OUTPUT);
  pinMode(output9, OUTPUT);
  pinMode(output37, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output7, LOW);
  digitalWrite(output8, LOW);
  digitalWrite(output9, LOW);
  digitalWrite(output37, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }
              else if (header.indexOf("GET /7/on") >= 0) {
              Serial.println("GPIO 7 on");
              output7State = "on";
              digitalWrite(output7, HIGH);
            } else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("GPIO 7 off");
              output7State = "off";
              digitalWrite(output7, LOW);
            } else if (header.indexOf("GET /8/on") >= 0) {
              Serial.println("GPIO 8 on");
              output8State = "on";
              digitalWrite(output8, HIGH);
            } else if (header.indexOf("GET /8/off") >= 0) {
              Serial.println("GPIO 8 off");
              output8State = "off";
              digitalWrite(output8, LOW);
            }
              else if (header.indexOf("GET /9/on") >= 0) {
              Serial.println("GPIO 9 on");
              output9State = "on";
              digitalWrite(output9, HIGH);
            } else if (header.indexOf("GET /9/off") >= 0) {
              Serial.println("GPIO 9 off");
              output9State = "off";
              digitalWrite(output9, LOW);
            } else if (header.indexOf("GET /37/on") >= 0) {
              Serial.println("GPIO 37 on");
              output37State = "on";
              digitalWrite(output37, HIGH);

              



            } else if (header.indexOf("GET /37/off") >= 0) {
              Serial.println("GPIO 37 off");
              output37State = "off";
              digitalWrite(output37, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Se tocar o buzzer perde</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            // If the output26State is off, it displays the ON button       
            if (output1State=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">??</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">Safe</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            // If the output2State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">??</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">Safe</button></a></p>");
            }
            client.println("</body></html>");

                        // Display current state, and ON/OFF buttons for GPIO 26  
            // If the output9State is off, it displays the ON button       
            if (output9State=="off") {
              client.println("<p><a href=\"/9/on\"><button class=\"button\">??</button></a></p>");
            } else {
              client.println("<p><a href=\"/9/off\"><button class=\"button button2\">Safe</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            // If the output37State is off, it displays the ON button       
            if (output37State=="off") {
              client.println("<p><a href=\"/37/on\"><button class=\"button\">??</button></a></p>");
            } else {
              client.println("<p><a href=\"/37/off\"><button class=\"button button2\">PERDEU</button></a></p>");
            }
            client.println("</body></html>");

                        // Display current state, and ON/OFF buttons for GPIO 26  
            // If the output7State is off, it displays the ON button       
            if (output7State=="off") {
              client.println("<p><a href=\"/7/on\"><button class=\"button\">??</button></a></p>");
            } else {
              client.println("<p><a href=\"/7/off\"><button class=\"button button2\">Safe</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            
            // If the output8State is off, it displays the ON button       
            if (output8State=="off") {
              client.println("<p><a href=\"/8/on\"><button class=\"button\">??</button></a></p>");
            } else {
              client.println("<p><a href=\"/8/off\"><button class=\"button button2\">Safe</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}