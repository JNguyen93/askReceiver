// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module
//COM6
#include <RHDatagram.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
RHDatagram RHD = RHDatagram(driver, 1);
// RH_ASK driver(2000, 2, 4, 5); // ESP8266: do not use pin 11

void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("Receiver initializing");
    if (!RHD.init())
         Serial.println("init failed");
    Serial.print("This address is: ");
    Serial.println(RHD.thisAddress());
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    uint8_t from = 0;
    uint8_t to = 0;
    uint8_t id = 0;
    uint8_t flags = 0;
    //Serial.println(RHD.available());
    if (RHD.recvfrom(buf, &buflen, &from, &to, &id, &flags)) // Non-blocking
    {
      //driver.recv(buf, &buflen);
      for(int i = 0; i < buflen; i++){
        Serial.print("Received: ");
        Serial.println(i);
        Serial.println(buf[i], BIN);
      }
      Serial.print("From: ");
      Serial.println(from);
      Serial.print("To: ");
      Serial.println(to);
      Serial.print("ID: ");
      Serial.println(id);
      Serial.print("Flags: ");
      Serial.println(flags);
      //driver.printBuffer("Received:", buf, 2);
	    // Message with a good checksum received, dump it.
	    //driver.printBuffer("Got:", buf, buflen);
    }
}
