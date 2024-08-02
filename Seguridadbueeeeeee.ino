#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_V 6
#define LED_R 7
#define BUZZER 5

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_V, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "A6 DF C4 07") {
    digitalWrite(LED_V, HIGH);
    tone(BUZZER, 200);
    delay(4000);
    noTone(BUZZER);
    
    digitalWrite(LED_V, LOW);
  } else {
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 400);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
}
