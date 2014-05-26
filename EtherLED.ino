/*
 * WebCsm Server sketch
 * Turns pin 5 and 6 on and off using HTML form
 * Used to control Webcam Switches
 */

#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE };
byte ip[] =  { 172,30,1,99 };

const int MAX_PAGENAME_LEN = 8; // max characters in page name 
char buffer[MAX_PAGENAME_LEN+1]; // additional character for terminating null
String text;

EthernetServer server(80);
EthernetClient client;

void setup()
{
  Serial.begin(115200);
  Ethernet.begin(mac, ip);
  server.begin();
  delay(2000);
  
  Serial.print("font ");
  Serial.print("4");
  Serial.write(13);
  delay(100);
}

void loop()
{
  client = server.available();
  if (client) {
    int type = 0;
    while (client.connected()) 
      {
        if (client.available()) 
        {
        // GET, POST, or HEAD
        memset(buffer,0, sizeof(buffer)); // clear the buffer
        if(client.readBytesUntil('/', buffer,sizeof(buffer)))
        {                         
          //Serial.println(buffer);
          if(strcmp(buffer,"POST ") == 0){
            client.find("\n\r"); // skip to the body
            // find string starting with "pin", stop on first blank line
            // the POST parameters expected in the form pinDx=Y
            // where x is the pin number and Y is 0 for LOW and 1 for HIGH
            while(client.findUntil("text=", "\n\r")){
              String text = client.readString();
              text.replace("+", " ");
              paintTxt(text, 2);
            }
          }
          sendHeader(client,"EtherLED");
          //create HTML form to input text
          client.println("<h2>EtherLED</h2>");
          client.print(
          "<form action='/' method='POST'><p><input type='text' name='text'");
          client.print("><input type='submit' value='PAINT'/></form>");
          client.stop();
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}
void sendHeader(EthernetClient client, char *title)
{
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.print("<html><head><title>");
  client.print(title);
  client.println("</title><body>");
}  

void paintTxt(String text, int color)
{
    Serial.print("scroll ");
    Serial.print(color);
    Serial.print(" 0 7 80 \"");
    Serial.print(text);
    Serial.print("\"");
    Serial.write(13);
    delay(100);
    
    Serial.print("paint");
    Serial.write(13);   
}

void clearTxt()
{
    Serial.print("clear");
    Serial.write(13);
    delay(100);
}
