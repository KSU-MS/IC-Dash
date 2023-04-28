#include <Arduino.h>
#include "Adafruit_MCP23X17.h"

Adafruit_MCP23X17 mcp;

int Egn_Oht = 19;
int CS_Pin_T = 10;
int CS_Pin_IO = 7;


void setup()
{

  Serial.begin(9600); // Set Baud Rate
  mcp.begin_SPI(CS_Pin_T); // SPI Initialize on IO
  mcp.pinMode(Egn_Oht, OUTPUT); // Set pin on MCP as output
  }

void loop()
{

  //Testing
  mcp.digitalWrite(CS_Pin_T, HIGH); // CS Pin High
  mcp.digitalWrite(Egn_Oht, LOW);
  //End Testing
  }