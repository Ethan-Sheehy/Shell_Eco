// variables 
// const int motorpin=9; for brushed motor 
const int potpin=A0;
int pot;
int throttle;
int U_high = 11;
int V_high = 10;
int W_high = 9;
int U_low = 6;
int V_low = 5;
int W_low = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(7, INPUT);
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
  bool A = digitalRead(2); //pin 
  bool B = digitalRead(4);
  bool C = digitalRead(7);

  //create integer from 2-7
  unsigned int state = A<<2 | B<<1 | C;
  

 //Run through states
 //analogwrite(pin,value) 
  switch(state)
  {
    case 4: //State 1: Phase A on, B off, C off, 100
      digitalWrite(U_high, HIGH); 
      digitalWrite(U_low, LOW);
      digitalWrite(V_high,LOW);
      digitalWrite(V_low, LOW); 
      digitalWrite(W_high,LOW);
      digitalWrite(W_low, HIGH);
      Serial.println("4"); 
      break;
    case 5: //State 2: Phase A on, B off, C on, 101
      digitalWrite(U_high,HIGH); 
      digitalWrite(U_low, LOW);
      digitalWrite(V_high,LOW);
      digitalWrite(V_low, HIGH); 
      digitalWrite(W_high,LOW);
      digitalWrite(W_low, LOW);
      Serial.println("5");
      break;
    case 1: //State 3: Phase A off, B off, C on, 001
      digitalWrite(U_high,LOW); 
      digitalWrite(U_low, LOW);
      digitalWrite(V_high,LOW);
      digitalWrite(V_low, HIGH); 
      digitalWrite(W_high,HIGH);
      digitalWrite(W_low, LOW);
      Serial.println("1");
      break;
    case 3: //State 4: Phase A off, B on, C on, 011
      digitalWrite(U_high,LOW); 
      digitalWrite(U_low, HIGH);
      digitalWrite(V_high,LOW);
      digitalWrite(V_low, LOW); 
      digitalWrite(W_high,HIGH);
      digitalWrite(W_low, LOW);
      Serial.println("3");
      break;
    case 2: //State 5: Phase A off, B on, C off, 010
      digitalWrite(U_high,LOW); 
      digitalWrite(U_low, HIGH);
      digitalWrite(V_high,HIGH);
      digitalWrite(V_low, LOW); 
      digitalWrite(W_high,LOW);
      digitalWrite(W_low, LOW);
      Serial.println("2");
      break;
    case 6: //State 6: Phase A on, B on, C off, 110
      digitalWrite(U_high,LOW); 
      digitalWrite(U_low, LOW);
      digitalWrite(V_high,HIGH);
      digitalWrite(V_low, LOW); 
      digitalWrite(W_high,LOW);
      digitalWrite(W_low, HIGH);
      Serial.println("6");
      break;
    default:
      // Set code that can count number of defaults and shut system down with excessive faults 
      // Ignore/shutdown 
      break;
  }
}
