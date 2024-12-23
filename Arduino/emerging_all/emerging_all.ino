#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define dirPin 9
#define stepPin 10
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


const int trigPin = 6;
const int echoPin = 5;

long duration;
int distance;

int button = 7;

int x;
int dist;
void setup() {
  if(!mlx.begin()){
    while (1);
  };
  // Declare pins as output:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(button, INPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop(){
  int data = mlx.readObjectTempF();
  disp_send(data);
  //while(!Serial.available());
  x = Serial.readString().toInt();
  dist = distance_m();
  //Serial.println(dist);
  
  if(x>=90){
    if(dist<=30){
      if(data<=98){
        digitalWrite(dirPin, LOW);
        for (int i = 0; i < 100*stepsPerRevolution; i++) {
          int dataButton = digitalRead(button);
            if(dataButton == LOW){
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
              break;
            }
        }
      }
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

void disp_send(int data){
  while(!Serial.available());
  Serial.print(data);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("TAYYAB SHAH");
  display.setCursor(0,8);
  display.println(data);
  display.display();
  display.clearDisplay();
}
