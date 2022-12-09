#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>
// Servo definitions
Servo servo_x;
Servo servo_y;
// Pin definitions
#define echoPin 3
#define trigPin 2

long duration;
int distance;
const int rs = 10, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//const int xpin = 2;
//const int ypin = 3;

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  // Define Servo X variables
  pinMode(A0, INPUT);
  //servo_x.attach(xpin);
  // Define Servo y variables
  pinMode(A1, INPUT);
  //servo_y.attach(ypin);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  // Write the output of the joystick to the servos
  //servo_x.write(analogRead(A0));
  //servo_y.write(analogRead(A1));
  lcd.setCursor(0,0);
  lcd.print(distance);
  lcd.setCursor(4,0);
  lcd.print("cm");
  delay(200);
  lcd.clear();
}