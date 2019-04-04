// CAN Send Example
//

#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Set CS to pin 10

unsigned long n = 172;

unsigned int potPin = 0;
const int potDataSize = 2;
int tempPotData = 0;
byte potData[potDataSize];

void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

void loop()
{
  
  tempPotData = analogRead(potPin);
  
  potData[0] = (tempPotData >> 8) & 255; //convert the int into a byte array
  potData[1] = tempPotData & 255;
  Serial.println((potData[0])*256+(potData[1]));
  
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, potDataSize, potData);
  if(sndStat == CAN_OK){
    //Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);   // send data per 100ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
