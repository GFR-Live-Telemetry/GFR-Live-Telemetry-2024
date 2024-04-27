#include <CAN.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  //Serial.print("Sending packet ... ");

    CAN.beginPacket(0x14);
  CAN.write('T');
  CAN.write('h');
  CAN.write('r');
  CAN.write('o');
  CAN.write('t');
  CAN.write('l');
  CAN.write('e');
  CAN.write('P');
  CAN.endPacket();


  delay(1000);

    CAN.beginPacket(0x15);
  CAN.write('B');
  CAN.write('r');
  CAN.write('a');
  CAN.write('k');
  CAN.write('e');
  CAN.write('P');
  CAN.write('o');
  CAN.write('s');
  CAN.endPacket();



  delay(1000);

    CAN.beginPacket(0x16);
  CAN.write('G');
  CAN.write('e');
  CAN.write('e');
  CAN.write('f');
  CAN.write('o');
  CAN.write('r');
  CAN.write('c');
  CAN.write('e');
  CAN.endPacket();

  

  delay(1000);
  Serial.println("done");
}