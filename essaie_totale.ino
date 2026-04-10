#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN 10  
#define RST_PIN 9 
#define trigPin 7 
#define echoPin 6
#define led 2 
#define led2 3  
#define buzzer 5
int sound = 250;
MFRC522 rfid(SS_PIN, RST_PIN);
Servo servo; 

// created by Armand BUKAMA for my undergraduate thesis project

void setup() {
Serial.begin (9600);  
SPI.begin();
rfid.PCD_Init();
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);
pinMode(led, OUTPUT); 
pinMode(led2, OUTPUT);
pinMode(buzzer, OUTPUT);
servo.attach(4);
servo.write(0);
}
void loop() {
if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Lire l'identifiant de la carte RFID
    String rfidTag = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      rfidTag += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      rfidTag += String(rfid.uid.uidByte[i], HEX);
    }
    Serial.println("RFID Tag: " + rfidTag);

    if (rfidTag == "b281931b") {
      Serial.println("Accès autorisé Bienvenu");
      servo.write(190);
      delay(2000);  // Attendre 2 secondes

      
      servo.write(0);
    } else {
      Serial.println("Accès non autorisé");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
long duration, distance; 
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); duration = pulseIn(echoPin, HIGH); distance = (duration/2) / 29.1;
if (distance <= 30) { 
  digitalWrite(led, HIGH); sound = 250;
}
else {
digitalWrite(led,LOW); }
if (distance < 25) { 
  digitalWrite(led2, HIGH); sound = 260;
}
else {
digitalWrite(led2, LOW);
}
if (distance < 20) {
digitalWrite(led2, HIGH);
sound = 270; }
else {
digitalWrite(led2, LOW);
}
if (distance < 5) {
digitalWrite(led2, HIGH);
delay(1500);
digitalWrite(led2, LOW);
delay(1500);
sound = 300; }
else { digitalWrite(led2,LOW);
}
if (distance > 30 || distance <= 0){ Serial.println("Aucun object detecté"); noTone(buzzer);
}
else {
Serial.print(distance); Serial.println(" cm"); tone(buzzer, sound);
}
delay(500); }
