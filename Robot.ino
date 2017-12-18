int Echo1 = A4;
int Trig1 = A5;
int ENA = 10;
int ENB = 11;
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
char data = 0;
bool light = false;
bool obstacle = false;
bool action = false;
int beap = 3;
int led = 4;
int motorspeed = 255;
int way = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(Echo1, INPUT);
  pinMode(Trig1, OUTPUT);
  pinMode(beap, OUTPUT);
  pinMode(led, OUTPUT);
}
 
void loop() {

    analogWrite(ENA, motorspeed);
    analogWrite(ENB, motorspeed);

    int d = detectObstacle();
    if (d <= 20) {
      digitalWrite(beap, HIGH);
      obstacle = true;
    }
    else{
      digitalWrite(beap, LOW);
      obstacle = false;
    }
    
  if(!obstacle && action){
    if(way == 1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    }
    else if(way == 3){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    }
    else if(way == 4){
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    }
  }
  
  if(action){
    if(way == 2){
    digitalWrite(in2,LOW);
    digitalWrite(in1,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in3,HIGH);
    }
  }
    
  if((obstacle && !(way == 2)) || !action){
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
  }

  if(Serial.available() > 0){
    data = Serial.read();
    if(data == 'o')
      light = true;
    else if(data == 's')
      light = false;
    else if(data == 'm')
      action = true;
    else if(data == 'x')
      action = false;
    else if(data == '+')
      speedup();
    else if(data == '-')
      speeddown();
    else if(data == 'f')
      way = 1;
    else if(data == 'b')
      way = 2;
    else if(data == 'r')
      way = 3;
    else if(data == 'l')
      way = 4;
  }
  
  if (light) {
    digitalWrite(led,HIGH);
  }
  else {
    digitalWrite(led,LOW);
  }
   
}

int detectObstacle() {
  digitalWrite(Trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig1, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig1, LOW);
  float distance = pulseIn(Echo1, HIGH);
  delay(10);
  distance = distance / 29 / 2;
  return distance;
}

void speedup(){
  if(motorspeed+51 <= 255){
  motorspeed += 51;
  }
}

void speeddown(){
  if(motorspeed-51 >= 0){
  motorspeed -= 51;
  }
}

