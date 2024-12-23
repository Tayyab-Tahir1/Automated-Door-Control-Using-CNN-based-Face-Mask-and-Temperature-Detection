#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int x;

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(1);

  if(!mlx.begin()){
    while (1);
  };
  
}

void loop(){
  while(!Serial.available());
  x = Serial.readString().toInt();
  int data = mlx.readObjectTempF();
  Serial.print(data);
  //delay(500);
}
