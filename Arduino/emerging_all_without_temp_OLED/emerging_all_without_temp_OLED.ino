#define dirPin 9
#define stepPin 10
#define stepsPerRevolution 200

const int trigPin = 6;
const int echoPin = 5;

long duration;
int distance;

int button = 7;

int x;
int dist;
void setup() {
  // Declare pins as output:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(button, INPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
}

void loop(){
  while(!Serial.available());
  x = Serial.readString().toInt();
  dist = distance_m();
  Serial.println(dist);
  
  if(x>=90){
    if(dist<=30){
      digitalWrite(dirPin, LOW);

      // Spin the stepper motor 1 revolution slowly:
      for (int i = 0; i < 100*stepsPerRevolution; i++) {
        int data = digitalRead(button);
          if(data == LOW){
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
