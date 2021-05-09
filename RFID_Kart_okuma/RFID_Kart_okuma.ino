#include <SPI.h>
#include <MFRC522.h>

int RST_PIN = 9;  //modül gerekli pin bağlantıları
int SS_PIN = 10;

MFRC522 rfid(SS_PIN, RST_PIN);

byte ID[4] = {0, 0, 0, 0};

void setup() {

  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {

  if (! rfid.PICC_IsNewCardPresent())
    return;
  if (! rfid.PICC_ReadCardSerial())
    return;

  if ( rfid.uid.uidByte[0] == ID[0] && rfid.uid.uidByte[1] == ID[1])
    Serial.println(" kapı açıldı");

  else
  { Serial.println(" YETKiSiZ KART");
    ekranayazdir();
  }
}
void ekranayazdir() {
  Serial.print(" ID Numarası: ");
  for (int i = 0; i <= 4; i++) {

    Serial.print(rfid.uid.uidByte[i]);
    Serial.print("  ");

  }
}
