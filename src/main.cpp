#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>
// Servo definitions
Servo servo_x;
Servo servo_y;
// Pin definitions
#define echoPin 3
#define trigPin 2
#define xpin_out 2
#define ypin_out 3
#define ypin_in A1
#define xpin_in A0
#define swPin 11
#define lsPin 12

const int rs = 10, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration;
int dist;

void setup() {
  // Set pins to correct OUT and IN
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(xpin_in, INPUT);
  pinMode(ypin_in, INPUT);
  pinMode(swPin, INPUT);
  pinMode(lsPin, OUTPUT);
  //Attach servo to pin
  servo_x.attach(xpin_out, 500, 2500);
  servo_y.attach(ypin_out, 500, 2500);
  // start Serial Monitor
  Serial.begin(9600);
  //start LCD
  lcd.begin(16, 2);
  // Create a function that measures and writes the distance to the screen
}

void loop() {
  // Makes sure the trigPin is LOW(inactive) before continuing
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  dist = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
  // Displays the distance on the display
  lcd.setCursor(0,0);
  lcd.print(dist);
  lcd.setCursor(4,0);
  lcd.print("cm");
  delay(200);
  lcd.clear();
  // Write the output of the joystick to the servos so they move
  servo_x.write(analogRead(xpin_in));
  servo_y.write(analogRead(ypin_in));
  // Check if the button is pressed and if it is fire the laser
  while (swPin == LOW){ // LOW because the joystick sends a low signal if the button is pressed
    digitalWrite(lsPin, HIGH);
  }
}