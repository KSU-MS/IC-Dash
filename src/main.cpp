#include <Arduino.h>
#include "FlexCAN_T4.h"
#include "Adafruit_MCP23X17.h"
#define NUM_TX_MAILBOXES 2
#define NUM_RX_MAILBOXES 6
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> ECU_CAN;

uint8_t data[8] = {9, 8, 7, 6, 5, 4, 0, 0};

Adafruit_MCP23X17 mcp;

#define Egn_Oht 19

#define CS_Pin 10


void setup()
{

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  mcp.pinMode(Egn_Oht, OUTPUT);
  // SPI Initialize
  if (!mcp.begin_SPI(CS_Pin)){
    Serial.println("Error on SPI Bus");
    while(1);
  }


  ECU_CAN.begin();
  ECU_CAN.setBaudRate(500000);
  ECU_CAN.setMaxMB(NUM_TX_MAILBOXES + NUM_RX_MAILBOXES);
  for (int i = 0; i < (NUM_RX_MAILBOXES - 1); i++)
  {
    ECU_CAN.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_MAILBOXES; i < (NUM_TX_MAILBOXES + NUM_RX_MAILBOXES); i++)
  {
    ECU_CAN.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }
  // put your setup code here, to run once:
}

void loop()
{

  //Testing
  mcp.digitalWrite(Egn_Oht, HIGH);
  //End Testing
  CAN_message_t RX_MSG;
  CAN_message_t TX_MSG;

  RX_MSG.id = 0x0B; // Find id on ECU

  ECU_CAN.read(RX_MSG);

  memcpy(RX_MSG.buf, data, TX_MSG.len);

  if (ECU_CAN.read(RX_MSG))
  {

    Serial.print("It worked");

    digitalWrite(LED_BUILTIN, HIGH);

    delay(500);

    digitalWrite(LED_BUILTIN, LOW);

  }

  if (RX_MSG.id == 11)
  {



  }

  switch (RX_MSG.id)
  {
  case 11:


    break;

  case 12:

  case 13:

  
  default:
    break;
  }

  // Serial.println(TX_MSG.id);

  // put your main code here, to run repeatedly:
}