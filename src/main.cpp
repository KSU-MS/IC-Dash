#include <Arduino.h>
#include <Metro.h>
#include "FlexCAN_T4.h"
#include "Adafruit_MCP23X17.h"
#include "CAN_ID.hpp"

#define DEBUG // Comment this on or off to enable debugging serial prints
#define TEST // Comment this on or off to enable test mode

// CANBUS stuff
#define NUM_TX_MAILBOXES 2
#define NUM_RX_MAILBOXES 6
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> ECU_CAN;

uint8_t data[8] = {9, 8, 7, 6, 5, 4, 0, 0};


// LED output pins
#define oilPressure_pin 33
#define oilTemp_pin 34
#define engineOverheat_pin 32
#define engineTemp_pin 40
#define launchControl_pin 41
#define cltFa_pin 35
#define CAN1Error_pin 21
#define CAN2Error_pin 2

// Metro timers
Metro heartTime = Metro(100);
Metro getECUCAN = Metro(100);
Metro updateDash = Metro(100);
Metro testingTime = Metro(3000);

void heartbeat();
void update_ECUCAN();


 // put your setup code here, to run once:
void setup()
{
  // Serial & CAN Initializations
  Serial.begin(9600);
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

  // PIN Initializations
  pinMode(LED_BUILTIN, OUTPUT); // This is for the heartbeat LED
  pinMode(oilPressure_pin, OUTPUT);
  pinMode(oilTemp_pin, OUTPUT);
  pinMode(engineOverheat_pin, OUTPUT);
  pinMode(engineTemp_pin, OUTPUT);
  pinMode(launchControl_pin, OUTPUT);
  pinMode(cltFa_pin, OUTPUT);
  pinMode(CAN1Error_pin, OUTPUT);
  pinMode(CAN2Error_pin, OUTPUT);
}


// put your main code here, to run repeatedly:
void loop()
{
  //Testing
  #ifdef TEST
    if(testingTime.check()){
      digitalToggle(oilPressure_pin);
      digitalToggle(oilTemp_pin);
      digitalToggle(engineOverheat_pin);
      digitalToggle(engineTemp_pin);
      digitalToggle(launchControl_pin);
      digitalToggle(cltFa_pin);
      digitalToggle(CAN1Error_pin);
      digitalToggle(CAN2Error_pin);
    }
  #endif
  //End Testing

  if(heartTime.check()){
    heartbeat();
  }

  if(getECUCAN.check()){
    update_ECUCAN();
  }

  CAN_message_t RX_MSG;
  CAN_message_t TX_MSG;

  if (ECU_CAN.read(RX_MSG))
  {
    Serial.print("It worked");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }


  // Serial.println(TX_MSG.id);
}


void heartbeat(){
  digitalToggle(LED_BUILTIN);
}

void update_ECUCAN(){
  CAN_message_t RX_MSG;
  if(ECU_CAN.read(RX_MSG)){
    switch (RX_MSG.id)
    {
      case (ID_RPM):
      {
          // Do more stuff
          break;
      }
      case (ID_CLT):
      {
          // DO stuff
          break;
      }
      default:
      {
        break;
      }
    }
  }
}