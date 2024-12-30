#include <CAN.h>

#define TX_GPIO_NUM   32
#define RX_GPIO_NUM   34

uint64_t packetIdCount = 0;
uint8_t byte0Test = 0;
uint8_t byte1Test = 100;
uint8_t packetFrameTest[8] = {};

void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1000);

  Serial.println ("CAN Sender");

  // Set the pins
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);

  // start the CAN bus at 500kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  
  Serial.print("Sending packet ID: ");
  // Serial.println(packetIdCount);
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  // CAN.beginPacket(packetIdCount);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  // Serial.print("Sending extended packet ... ");
  // CAN.beginExtendedPacket(0xabcdef);
  // CAN.beginExtendedPacket(packetIdCount);

  CAN.beginExtendedPacket(0x28);
  for(int i = 0; i < 7; i++)
  {
    CAN.write(packetFrameTest[i]);
  }
  CAN.endPacket();

  // CAN.write(0);
  // CAN.write(0x01);
  // CAN.write(0x2c);
  // CAN.write(0x03);
  // CAN.write(0xa9);
  // CAN.write(0);
  // CAN.write(0);
  // CAN.write(0);
  // CAN.endPacket();

  Serial.println("done");

  delay(32);
  packetFrameTest[2]++;
  if(packetFrameTest[2] == 255)
  {
    packetFrameTest[2] = 0;
    packetFrameTest[1]++;
    if(packetFrameTest[1] == 8)
    {
      packetFrameTest[1] = 0; 
    }
  }

  packetFrameTest[4]++;
  if(packetFrameTest[4] == 255)
  {
    packetFrameTest[4] = 0;
    packetFrameTest[3]++;
    if(packetFrameTest[3] == 3)
    {
      packetFrameTest[3] = 0; 
    }
  }
  // packetIdCount++;
  // byte0Test++;
  // byte1Test--;
  // if(packetIdCount > 65565)
  // {
  //   packetIdCount = 0;
  // }
  // if(byte0Test > 64)
  // {
  //   byte0Test = 0;
  // }
  // if(byte1Test < 1)
  // {
  //   byte1Test = 64;
  // }
  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  // Serial.print("Sending extended packet ... ");

  // CAN.beginExtendedPacket(0xabcdef);
  // CAN.write('w');
  // CAN.write('o');
  // CAN.write('r');
  // CAN.write('l');
  // CAN.write('d');
  // CAN.endPacket();

  // Serial.println("done");

  // delay(100);
}