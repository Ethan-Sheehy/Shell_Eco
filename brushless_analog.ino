// variables 
// const int motorpin=9; for brushed motor 
const int potpin=A0;
int pot;
int throttle;
int U_high = 7;
int U_low = 6;
int V_high = 5;
int V_low = 4;
int W_high = 3;
int W_low = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(U_high, OUTPUT);
  pinMode(U_low, OUTPUT);
  pinMode(V_high, OUTPUT);
  pinMode(V_low, OUTPUT);
  pinMode(W_high, OUTPUT);
  pinMode(W_low, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //add code that sets limit for actual motor
 // read potentiometer (0-1023) 
  pot = analogRead (potpin);
  // convert to 0-255
  throttle = map(pot,0,1023,0,255);
  // set motor speed 
  //analogWrite (motorpin,throttle);  //old code for sending potentiometer reading 
  
  //Read Hall Effect 
  bool A = digitalRead(8); //pin 
  bool B = digitalRead(9);
  bool C = digitalRead(10);

  //create integer from 2-7
  unsigned int state = A<<2 | B<<1 | C;
  

 //Run through states
 //analogwrite(pin,value) 
  switch(state)
  {
    case 4: //State 1: Phase A on, B off, C off, 100
      analogWrite(U_high,throttle); 
      analogWrite(U_low, 0);
      analogWrite(V_high,0);
      analogWrite(V_low, 0); 
      analogWrite(W_high,0);
      analogWrite(W_low, throttle);
      Serial.println("4"); 
      break;
    case 5: //State 2: Phase A on, B off, C on, 101
      analogWrite(U_high,throttle); 
      analogWrite(U_low, 0);
      analogWrite(V_high,0);
      analogWrite(V_low, throttle); 
      analogWrite(W_high,0);
      analogWrite(W_low, 0);
      Serial.println("5");
      break;
    case 1: //State 3: Phase A off, B off, C on, 001
      analogWrite(U_high,0); 
      analogWrite(U_low, 0);
      analogWrite(V_high,0);
      analogWrite(V_low, throttle); 
      analogWrite(W_high,throttle);
      analogWrite(W_low, 0);
      Serial.println("1");
      break;
    case 3: //State 4: Phase A off, B on, C on, 011
      analogWrite(U_high,0); 
      analogWrite(U_low, throttle);
      analogWrite(V_high,0);
      analogWrite(V_low, 0); 
      analogWrite(W_high,throttle);
      analogWrite(W_low, 0);
      Serial.println("3");
      break;
    case 2: //State 5: Phase A off, B on, C off, 010
      analogWrite(U_high, 0); 
      analogWrite(U_low, throttle);
      analogWrite(V_high,throttle);
      analogWrite(V_low, 0); 
      analogWrite(W_high,0);
      analogWrite(W_low, 0);
      Serial.println("2");
      break;
    case 6: //State 6: Phase A on, B on, C off, 110
      analogWrite(U_high,0); 
      analogWrite(U_low, 0);
      analogWrite(V_high,throttle);
      analogWrite(V_low, 0); 
      analogWrite(W_high,0);
      analogWrite(W_low, throttle);
      Serial.println("6");
      break;
    default:
      // Set code that can count number of defaults and shut system down with excessive faults 
      // Ignore/shutdown 
      break;
  }
}