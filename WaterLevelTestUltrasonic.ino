
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 9; 
const int echoPin = 10;
float duration, distance; 
Servo myServo1, myServo2;

int RedLED = 4;
int YellowLED = 3;
int GreenLED = 2;
int servoPos = 0;

void setup() {
 pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT); 
 pinMode(RedLED, OUTPUT);
 pinMode(YellowLED, OUTPUT);
 pinMode(GreenLED, OUTPUT);
 Serial.begin(9600); 
 myServo1.attach(5);
 myServo2.attach(6);

 
}
float calculation(){
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH); 
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW); 
 duration = pulseIn(echoPin, HIGH); 
 distance = (duration*.0343)/2; 
 Serial.print("Distance: "); 
 Serial.println(distance); 
 delay(100); 
 return distance;
}


void loop() { 
 calculation(); 
 if(distance >= 8){
  trafficGreen();
  servoOpen();
 }
 else if(distance <= 4){
  trafficRed();
  servoClose();
 }
 else{
  trafficYellow();
 }
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.print("Water Level:");
  display.println(distance);
  display.display(); 

 
}


void servoClose(){
    myServo1.write(90);
    myServo2.write(90);
    delay(15);
}
void servoOpen(){
    myServo1.write(0);
    myServo2.write(0);
    delay(15);
}



void trafficRed(){
  delay(100);
  digitalWrite(RedLED, HIGH);
  digitalWrite(YellowLED, LOW);
  digitalWrite(GreenLED, LOW);
 }
void trafficYellow(){
  delay(100);
  digitalWrite(RedLED, LOW);
  digitalWrite(YellowLED, HIGH);
  digitalWrite(GreenLED, LOW);
 }
void trafficGreen(){
  delay(100);
  digitalWrite(RedLED, LOW);
  digitalWrite(YellowLED, LOW);
  digitalWrite(GreenLED, HIGH);
 }
