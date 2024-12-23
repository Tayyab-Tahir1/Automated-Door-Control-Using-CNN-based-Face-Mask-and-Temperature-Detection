int x;
int led = 12;

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(led, OUTPUT);
}

void loop(){
  while(!Serial.available());
  x = Serial.readString().toInt();
  Serial.print(x);
  if(x >= 90){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
}
