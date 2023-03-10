#include <SPI.h>
#include <LoRa.h>

//======================================================================//

#define PIN_LORA_COPI   23
#define PIN_LORA_CIPO   19
#define PIN_LORA_SCK    18
#define PIN_LORA_CS     5
#define PIN_LORA_RST    2
#define PIN_LORA_DIO0   4

#define LORA_FREQUENCY  433E6

//======================================================================//

void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1500);
  Serial.println ("LoRa Receiver");

  LoRa.setPins (PIN_LORA_CS, PIN_LORA_RST, PIN_LORA_DIO0);
  LoRa.setSPIFrequency (20000000);

  if (!LoRa.begin (LORA_FREQUENCY)) {
    Serial.println ("Starting LoRa failed!");
    while (1);
  }
  else {
    Serial.print ("LoRa initialized with frequency ");
    Serial.println (LORA_FREQUENCY);
  }
}

//======================================================================//

void loop() {
  // try to parse packet
  //Hàm này dùng để đọc gói dữ liệu nhận được, đưa dữ liệu vào buffer. Hàm trả về size của gói dữ liệu
  int packetSize = LoRa.parsePacket();
  
  //Kiểm tra xem đã nhận được packet hay chưa
  if (packetSize) { 
    // received a packet
    Serial.print ("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print ((char) LoRa.read());    //read(): trả về 1 byte mỗi lần đọc
    }

    // print RSSI (Receive Signal Strenth Indication) of packet - received signal power
    Serial.print ("' with RSSI ");
    Serial.println (LoRa.packetRssi());
  }
}

//======================================================================/