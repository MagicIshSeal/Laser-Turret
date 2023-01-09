#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <ezButton.h>
// Servo definitions
Servo servo_x;
Servo servo_y;
// Pin definitions
#define echoPin 3
#define trigPin 2
#define xpin_out 11
#define ypin_out 12
#define ypin_in A1
#define xpin_in A0
#define swPin 4
#define lsPin 13

const int rs = 10, en = 9, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration;
int dist;
int xval;
int yval;


void setup() {
  // Set pins to correct OUT and IN
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(xpin_in, INPUT);
  pinMode(ypin_in, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(lsPin, OUTPUT);
  //Attach servo to pin
  servo_x.attach(xpin_out, 500, 2500);
  servo_y.attach(ypin_out, 500, 2500);
  // start Serial Monitor
  Serial.begin(9600);
  //start LCD
  lcd.begin(16, 2);
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
  // Displays the distance on the display
  lcd.setCursor(0,0);
  lcd.print(dist);
  lcd.setCursor(4,0);
  lcd.print("cm");
  delay(200);
  lcd.clear();
  Serial.print(analogRead(xpin_in));
  // Check if the button is pressed and if it is fire the laser
  if (digitalRead(swPin) == 0){
    digitalWrite(lsPin, HIGH);
  } else {
    digitalWrite(lsPin, LOW);
  }
  // Write the output of the joystick to the servos so they move
  xval = (0.17578125 * (analogRead(xpin_in))) + 1;
  yval = (0.17578125 * (analogRead(ypin_in))) + 1;
  servo_x.write(xval);
  servo_y.write(yval);
  
  
}