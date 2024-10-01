// variables 
const int motorpin=9;
const int potpin=A0;
int pot;
int speed;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
 // read potentiometer (0-1023) 
  pot = analogRead (potpin);
  // convert to 0-255
  speed = map(pot,0,1023,0,255);
  // set motor speed 
  analogWrite (motorpin,speed);
}
