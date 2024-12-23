#define dirPin 9
#define stepPin 10
#define stepsPerRevolution 200
int x;
//int led = 12;

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(1);
  
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop(){
  while(!Serial.available());
  x = Serial.readString().toInt();
  Serial.print(x);
  if(x >= 90){
      digitalWrite(dirPin, HIGH);
  
    // Spin the stepper motor 1 revolution slowly:
    for (int i = 0; i < 0.5*stepsPerRevolution; i++) {
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  }

  delay(2000);

  digitalWrite(dirPin, LOW);
  
    // Spin the stepper motor 1 revolution slowly:
    for (int i = 0; i < 0.5*stepsPerRevolution; i++) {
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  
}
