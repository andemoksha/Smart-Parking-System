#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Address: 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic Sensor 1
const int trig1 = 2;
const int echo1 = 3;

// Ultrasonic Sensor 2
const int trig2 = 4;
const int echo2 = 5;

// LEDs indicating slot status
const int led1 = 6;
const int led2 = 7;

// Variables
long duration1, duration2;
float distance1, distance2;
int vacantSlots;

// Function to measure distance
float getDistance(int trigPin, int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

long duration = pulseIn(echoPin, HIGH);

float distance = duration * 0.034 / 2;
return distance;


}

void setup()
{
// Sensor Pins
pinMode(trig1, OUTPUT);
pinMode(echo1, INPUT);


pinMode(trig2, OUTPUT);
pinMode(echo2, INPUT);

// LED Pins
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);

// LCD Initialization
lcd.init();
lcd.backlight();

// Serial Monitor (Optional)
Serial.begin(9600);

lcd.setCursor(0, 0);
lcd.print("Parking System");
delay(2000);
lcd.clear();


}

void loop()
{
// Read distances
distance1 = getDistance(trig1, echo1);
distance2 = getDistance(trig2, echo2);


vacantSlots = 0;

// Slot 1
if (distance1 > 10)
{
    digitalWrite(led1, HIGH);   // Vacant
    vacantSlots++;
}
else
{
    digitalWrite(led1, LOW);    // Occupied
}

// Slot 2
if (distance2 > 10)
{
    digitalWrite(led2, HIGH);   // Vacant
    vacantSlots++;
}
else
{
    digitalWrite(led2, LOW);    // Occupied
}

// LCD Display
lcd.clear();

lcd.setCursor(0, 0);
lcd.print("Vacant: ");
lcd.print(vacantSlots);

lcd.setCursor(0, 1);
lcd.print("S1:");
lcd.print((int)distance1);

lcd.print(" S2:");
lcd.print((int)distance2);

// Serial Output
Serial.print("Slot1: ");
Serial.print(distance1);
Serial.print(" cm | Slot2: ");
Serial.print(distance2);
Serial.print(" cm | Vacant: ");
Serial.println(vacantSlots);

delay(1000);


}
