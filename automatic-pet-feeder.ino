#include <Servo.h>
#include <HX711_ADC.h>
#include <Wire.h>

int jarak = 22;
int toleransi = 2;
int servo1 = 4;
int trig = 2;
int echo = 3;
int sck = 8;
int dt = 9;

int distance;
int length;
float berat;

Servo servo;
HX711_ADC scale(dt, sck); 

void setup() {
  Serial.begin(9600);
  Serial.println("cekk");
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(servo1);
  servo.write(90);

  scale.begin();
  delay(1000);
  scale.start(2000);
  scale.setCalFactor(388.5);

  Wire.begin();
}

void loop() {

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  length = pulseIn(echo, HIGH);
  distance = (length / 2) / 29.1;

  scale.update();
  berat = scale.getData();
  if(berat < 0) berat = 0;

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.print(" cm, Berat: ");
  Serial.print(berat);
  Serial.println(" gram");

  {
    if (distance >= jarak) 
    { 
      Serial.println("Makanan habis.");
      servo.write(90);
    } 
    else if (berat < 5) 
    {
      Serial.println("Berat kurang dari 5 gram. Memberi makanan...");
      servo.write(110);  
      delay(1000);
      servo.write(90);   
    } 
    else 
    {
      servo.write(90);   
    }

  delay(500);
}
