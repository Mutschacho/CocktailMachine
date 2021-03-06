#include <SoftwareSerial.h>

  int i;
  int k; // nombre de positions à parcourir entre i-1 et i
  int steps; //nombre de steps à parcourir entre i-1 et i
  int t=1600; //nombre de steps dans un tour, ici 1600
  int n=2; //nombre de tours entre deux positions      
  int GREEN_LED = 9;    
  int BLUE_LED = 10;
  int RED_LED = 11;
  int CONTROL_LED = 12;
  int statebt = 0;
  int NUMBER_COCKTAILS = 2;
  int ledblanc =22;
  int ledvert = 23;
  int ledrouge = 24;
  int ledvert = 25;
  int ledbleu = 26;
  const int stepPin = 4; 
  const int dirPin = 5; 
  const int enPin = 6;
  long time = 0;         // the last time the output pin was toggled
  long debounce = 100;   // the debounce time, increase if the output flickers
  int maxComp = 10;
  
  char cocktails[2][10] = {  
    //initialisation des cocktails
    "cdbea", //mojito
    "eda", //washmash
  };
  
void setup() {
  pinMode(ledblanc,OUTPUT);
  pinMode(ledvert,OUTPUT);
  pinMode(ledrouge,OUTPUT);
  pinMode(ledjaune,OUTPUT);
  pinMode(ledbleu,OUTPUT);
  pinMode(enPin,OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(CONTROL_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  Serial1.begin(9600);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  
  digitalWrite(enPin,LOW);
  
  if (statebt == 0) {
   //What to do when idle (for example, wait).
   Serial.println(statebt);
   digitalWrite(CONTROL_LED, HIGH);
   delay(2000);
 }
  if(statebt == 0 && Serial1.available() > 0){
   statebt = Serial1.read();
 }
  
  
  if (0 < statebt && statebt <= NUMBER_COCKTAILS) {
       Serial.println(statebt);

    digitalWrite(GREEN_LED - 1 + statebt, HIGH); //indique le cocktail qui est fait
    digitalWrite(CONTROL_LED, LOW);
    
    int pinDisplayed;
    int positionNext;
    int positionNow = 0; //the cart starts at the base, which is position 0
    for (i = 0 ; i <= (maxComp-1) ; i++) {
      
      switch (cocktails[statebt-1][i]) {
        case 'a' : //base
          pinDisplayed = 22;
          positionNext = 0;
          break;
        case 'b' : //menthe
          pinDisplayed = 23;
          positionNext = 1;
          break;
        case 'c' : //rhum
          pinDisplayed = 24;
          positionNext = 2;
          break;
        case 'd' : //citron
          pinDisplayed = 25;
          positionNext = 3;
          break;
        case 'e' : //curacao
          pinDisplayed = 26;
          positionNext = 4;
          break;        
      }
      
      k = positionNext - positionNow; //delta positions
      
      positionNow = positionNext;
      
      Serial.println(positionNext);
      
  
      if (k > 0) {
        // positive -> cockwise
        digitalWrite(dirPin,HIGH);
      } else { //negative -> counterclockwise
        digitalWrite(dirPin,LOW);
      }
      
      steps = n*abs(k)*t; 
      Serial.println(steps);
      for(int x = 0; x < steps; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(100); 
        digitalWrite(stepPin,LOW);
        delayMicroseconds(100); 
      }
      delay(500);
      digitalWrite(pinDisplayed,HIGH); //open the valve
      delay(1000);
      digitalWrite(pinDisplayed,LOW); //close the valve
      delay(1000);
      
      if(cocktails[statebt-1][i] == 'a') {
        break;
      }
    } 
    
    delay(2000);
    digitalWrite(GREEN_LED - 1 + statebt, LOW);
    delay(500);
    
    statebt = 0; //goes back to idle
  } 
}
