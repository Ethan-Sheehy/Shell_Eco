// variables 
// const int motorpin=9; for brushed motor 
const int potpin=A0;
int pot;
unsigned int throttle;
const int U_high = 11;
const int V_high = 10;
const int W_high = 9;
const int U_low = 6;
const int V_low = 5;
const int W_low = 3;

//Warning variables
int temp_counter = 0;
const int TempPin = 13;
unsigned int TempValue = 0;

//Shutdown, shutdown set to false unless warnings flare 
bool shutdown = false;

void setup() {
  // Set Timers 
  // Set Timer0 (Pins 5 & 6) to 31kHz
  TCCR0B = (TCCR0B & 0b11111000) | 0b001; 
  
  // Set Timer1 (Pins 9 & 10) 
  TCCR1B = (TCCR1B & 0b11111000) | 0b001; 
  TCCR1A = (TCCR1A & 0b00111111) | 0b10000000;

  //Set Timer2 (Pins 3 & 11)
  TCCR2B = (TCCR2B & 0b11111000) | 0b001;
  TCCR2A = (TCCR2A & 0b00111111) | 0b00000001; 
  
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

//Warning setup
  pinMode(TempPin, INPUT);

}

const bool DEBUG = 1;  //Used for debug mode, set = 1 to enable 
void loop() {
  // put your main code here, to run repeatedly:

//Check warnings before normal motor settings 
  //Temperature reading
  TempValue = digitalRead(TempPin);
    if (TempValue == HIGH) {
      temp_counter++;
      if (temp_counter > 2) {
        shutdown = true;
        Serial.println("Shutdown caused by excessive motor temperature");
      }
    }
  //count number of defaults 
//Nomral Motor settings 
  long startTime = micros();
  pot = analogRead (potpin);
  // convert to 0-255
  throttle = map(pot,0,1023,0,255);  //limit throttle range after known values 
  // set motor speed 
  //analogWrite (motorpin,throttle);  //old code for sending potentiometer reading 
  
  //Read Hall Effect 
  bool A = digitalRead(2); //pin 
  bool B = digitalRead(4);
  bool C = digitalRead(7);

  //create integer from 2-7
  unsigned int state = A<<2 | B<<1 | C;
  
//Shutdown flag
  if (shutdown==true) {
    //throttle = 0;
    Serial.println("Motor no worko");
    state=10;
  }
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
      if(DEBUG){Serial.println("4");}
      break;
    case 5: //State 2: Phase A on, B off, C on, 101
      analogWrite(U_high,throttle); 
      analogWrite(U_low, 0);
      analogWrite(V_high,0);
      analogWrite(V_low, throttle); 
      analogWrite(W_high,0);
      analogWrite(W_low, 0);
      if(DEBUG){Serial.println("5");}
      break;
    case 1: //State 3: Phase A off, B off, C on, 001
      analogWrite(U_high,0); 
      analogWrite(U_low, 0);
      analogWrite(V_high,0);
      analogWrite(V_low, throttle); 
      analogWrite(W_high,throttle);
      analogWrite(W_low, 0);
      if(DEBUG){Serial.println("1");}
      break;
    case 3: //State 4: Phase A off, B on, C on, 011
      analogWrite(U_high,0); 
      analogWrite(U_low, throttle);
      analogWrite(V_high,0);
      analogWrite(V_low, 0); 
      analogWrite(W_high,throttle);
      analogWrite(W_low, 0);
      if(DEBUG){Serial.println("3");}
      break;
    case 2: //State 5: Phase A off, B on, C off, 010
      analogWrite(U_high, 0); 
      analogWrite(U_low, throttle);
      analogWrite(V_high,throttle);
      analogWrite(V_low, 0); 
      analogWrite(W_high,0);
      analogWrite(W_low, 0);
      if(DEBUG){Serial.println("2");}
      break;
    case 6: //State 6: Phase A on, B on, C off, 110
      analogWrite(U_high,0); 
      analogWrite(U_low, 0);
      analogWrite(V_high,throttle);
      analogWrite(V_low, 0); 
      analogWrite(W_high,0);
      analogWrite(W_low, throttle);
      if(DEBUG){Serial.println("6");}
      break;
    case 10:
      // SET ALL THE DRIVER PINS TO A FAILSAFE CONDITION
      analogWrite(U_high,0); 
      analogWrite(U_low, 0);
      analogWrite(V_high,0);
      analogWrite(V_low, 0); 
      analogWrite(W_high,0);
      analogWrite(W_low, 0);
      break;
    default:
      // Set code that can count number of defaults and shut system down with excessive faults 
      // Ignore/shutdown 
      break;
  }
  
  long endTime = micros();

  long loop_duration = endTime - startTime;
  //Serial.println(loop_duration);
}
