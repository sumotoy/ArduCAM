// ArduCAM Mini demo (C)2015 Lee
// web: http://www.ArduCAM.com
// This program is a demo for ESP8266 arduino board.
// Publish captured image to a webpage.
//
// This demo was made for ArduCAM Mini OV2640 2MP Camera.
// It needs to be used in combination with html webpage.
//

// This version uses the last sumotoy changes to work


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <Wire.h>
#include <SPI.h>
#include <ArduCAM.h>
#include <WebSocketServer.h>

// Enabe debug tracing to Serial port.
#define DEBUGGING

// Here we define a maximum framelength to 64 bytes. Default is 256.
#if defined MAX_FRAME_LENGTH
  #undef MAX_FRAME_LENGTH
  #define MAX_FRAME_LENGTH 64
#endif

// Define how many callback functions you have. Default is 1.
#define CALLBACK_FUNCTIONS 1


const int CS = 16;

const char* ssid = "your sid";
const char* password = "your sid pass";


// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
WebSocketServer webSocketServer;

void read_fifo_burst(ArduCAM myCAM);

ArduCAM myCAM(OV2640, CS);


void setup() {

  uint8_t vid, pid;
  uint8_t temp;

  Serial.begin(115200);
  Serial.println("\nArduCAM Start!");
  myCAM.begin();

  //Check if the ArduCAM SPI bus is OK
  myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
  temp = myCAM.read_reg(ARDUCHIP_TEST1);
  if (temp != 0x55)
  {
    Serial.println("SPI1 interface Error!");
  }

  //Check if the camera module type is OV2640
  myCAM.wrSensorReg8_8(0xff, 0x01);
  myCAM.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
  myCAM.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
  if ((vid != 0x26) || (pid != 0x42))
    Serial.println("Can't find OV2640 module!");
  else
    Serial.println("OV2640 detected.");

  //Change to JPEG capture mode and initialize the OV2640 module
  myCAM.set_format(JPEG);
  myCAM.InitCAM();
  myCAM.OV2640_set_JPEG_size(OV2640_320x240);
  //myCAM.OV2640_set_JPEG_size(OV2640_640x480);
  myCAM.clear_fifo_flag();
  myCAM.write_reg(ARDUCHIP_FRAMES, 0x00);

  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

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
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  String data;
  int total_time = 0;

  WiFiClient client = server.available();
  if (webSocketServer.handshake(client)) {
    while (client.connected() )
    {
      data = webSocketServer.getData();
      if (data.length() > 0)
      {
        handleClientData(data);
      }

      if (myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK))
      {
        Serial.println("CAM Capture Done!");
        total_time = millis();
        read_fifo_burst(myCAM);
        total_time = millis() - total_time;
        Serial.print("total_time used (in miliseconds):");
        Serial.println(total_time, DEC);
        Serial.println("CAM send Done!");
        //Clear the capture done flag
        myCAM.clear_fifo_flag();

      }
    }

  }
  // This delay is needed to let the WiFi respond properly(very important)
  delay(100);
}

void handleClientData(String &dataString)
{
  if (dataString.startsWith("capture"))
  {
    Serial.println(dataString);
    start_capture();
  }
}

// send the client the analog value of a pin
void sendClientData(char *data, int size, unsigned char header) {
  webSocketServer.sendData(data, size, header);
}


void start_capture()
{
  myCAM.flush_fifo();
  myCAM.clear_fifo_flag();
  myCAM.start_capture();
}

void read_fifo_burst(ArduCAM myCAM)
{
  uint8_t temp, temp_last;
  static int i = 0;
  static uint8_t first_packet = 1;
  byte buf[2048];
  uint32_t length = 0;

  length = myCAM.read_fifo_length();
  if (length >= 393216 ) // 384kb
  {
    Serial.println("Over size.");
    return;
  }
  if (length == 0 ) //0 kb
  {
    Serial.println("Size is 0.");
    return;
  }
  myCAM.startSend();
  myCAM.set_fifo_burst();//Set fifo burst mode
  myCAM.sendData(0x00);
  //Read JPEG data from FIFO
  while ( (temp != 0xD9) | (temp_last != 0xFF))
  {
    temp_last = temp;
    temp = myCAM.sendData(0x00);
    if (i < 2048)
    {
      buf[i++] = temp;
      //yield();
    }
    else
    {
      if (first_packet == 1)
      {
        sendClientData((char*)buf, 2048, 0x02);
        first_packet = 0;
      }
      else
      {
        sendClientData((char*)buf, 2048, 0x00);
      }
      i = 0;
      buf[i++] = temp;

    }
    //yield();
  }
  if (i > 0)
  {
    sendClientData((char*)buf, i, 0x80);
    i = 0;
    first_packet = 1;
  }
  //yield();
  myCAM.endSend();
}