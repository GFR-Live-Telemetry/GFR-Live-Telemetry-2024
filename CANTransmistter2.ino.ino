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

  CAN.beginPacket(0x11);
  CAN.write('B');
  CAN.write('a');
  CAN.write('t');
  CAN.write('t');
  CAN.write('r');
  CAN.write('e');
  CAN.write('y');
  CAN.write('L');
  CAN.endPacket();



  delay(1000);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  //Serial.print("Sending extended packet ... ");

  CAN.beginPacket(0x12);
  CAN.write('s');
  CAN.write('t');
  CAN.write('e');
  CAN.write('a');
  CAN.write('n');
  CAN.write('g');
  CAN.write('l');
  CAN.write('e');
  CAN.endPacket();



  delay(1000);

    CAN.beginPacket(0x13);
  CAN.write('C');
  CAN.write('a');
  CAN.write('r');
  CAN.write('s');
  CAN.write('p');
  CAN.write('e');
  CAN.write('e');
  CAN.write('d');
  CAN.endPacket();



  delay(1000);
  Serial.println("done");

}
