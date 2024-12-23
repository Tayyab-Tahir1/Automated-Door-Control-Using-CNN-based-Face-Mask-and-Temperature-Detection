#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define dirPin 9
#define stepPin 8
#define stepsPerRevolution 200
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };


const int trigPin = 12;
const int echoPin = 11;

long duration;
int distance;

int openGate = 6;
int closeGate = 7;
int greenLed = 3;
int redLed = 2;

int x;
int dist;
int maskTemp = 0;
void setup() {
  if(!mlx.begin()){
    while (1);
  };
  // Declare pins as output:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(openGate, INPUT);
  pinMode(closeGate, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  if(digitalRead(closeGate)==LOW){
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
  else{
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop(){
  int TempData = mlx.readObjectTempF();
  int ambientData = mlx.readAmbientTempC();
  //while(!Serial.available());
  x = Serial.readString().toInt();
  dist = distance_m();
  disp_send(TempData,ambientData,dist);
  //Serial.println(dist);
  if(x<99){
    maskTemp = 0;
  }
  if(x>=99){
    if(dist<=70){
      if(TempData<=98){
        maskTemp = maskTemp + x;
        if(maskTemp>=10000){
          digitalWrite(redLed, HIGH);
          digitalWrite(greenLed, LOW);
        digitalWrite(dirPin, LOW);
        for (int i = 0; i < 100*stepsPerRevolution; i++) {
          int openValue = digitalRead(openGate);
            if(openValue == LOW){
              digitalWrite(stepPin, HIGH);
              delayMicroseconds(500);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(500);
            }
            else{
              digitalWrite(stepPin, LOW);
              delayMicroseconds(500);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(500);
              maskTemp = 0;
              break;
            }
        }
    //closing gate
    delay(4000);
        digitalWrite(dirPin, HIGH);
        for (int i = 0; i < 100*stepsPerRevolution; i++) {
          int closeValue = digitalRead(closeGate);
            if(closeValue == LOW){
              digitalWrite(stepPin, HIGH);
              delayMicroseconds(500);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(500);
            }
            else{
              digitalWrite(redLed, LOW);
              digitalWrite(greenLed, HIGH);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(500);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(500);
              break;
            }
        }
        delay(1000);
      }}
    }
    
  }

  

}



int distance_m(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}

void disp_send(int TempData, int ambientData, int dist){
  while(!Serial.available());
  Serial.print(TempData);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(" COVID-19 PROTECTION ");
  display.println("  PLEASE WEAR MASK");
  display.setCursor(0,22);
  display.print("Ambient Temp: ");
  display.setTextSize(2);
  display.print(ambientData);
  display.println("C");
  display.setTextSize(1);
  if(dist<=70){
    display.setCursor(0,38);
    display.print("Body Temp: ");
    display.setTextSize(2);
    display.print(TempData);
    display.println("F");
    display.setTextSize(1);
  }
  else{
    display.setTextSize(2);
    display.println("Stay close");
    display.setTextSize(1);
  }
  if(TempData>98){
    if(dist<=70){
      display.setCursor(0,56);
      display.println("HIGH BODY TEMPERATURE");  
    }
    
  }

  display.display();
  display.clearDisplay();
}
