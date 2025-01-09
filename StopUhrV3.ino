/*Stoppuhr

  Mayra Alejandra Diaz Romero
  
*/

// Bibliotheken 
#include <LiquidCrystal.h>

//Variablen
LiquidCrystal stoppUhr(7,6,5,4,3,2);
#define START_STOP 13
#define RESET 9
    //Zeit Variablen
unsigned long zeit;
unsigned long nextDeziSekunden = 100UL;
unsigned long nextSekunden = 1000UL;
unsigned long nextMinuten = 60000UL;
int deziSekunde = 0; 
int sekunde = 0;
int minute = 0; 
    //Schalter Variablen 
bool Start_Stop;
bool reset;
    //Reset millis()
extern volatile unsigned long timer0_millis;

void setup() {
  //Schalter SetUP
  pinMode(START_STOP,INPUT_PULLUP);
  pinMode(RESET,INPUT_PULLUP);
  //LCD SetUp
  stoppUhr.begin(16, 2);
  stoppUhr.setCursor(4, 0);
  stoppUhr.print("Stoppuhr");
  stoppUhr.setCursor(0,1);
  stoppUhr.print("00:00:0");
}

/*Reset*/

void resetUhr(){
  nextDeziSekunden = 100UL;
  nextSekunden = 1000UL;
  nextMinuten = 60000UL;
  deziSekunde = 0; 
  sekunde = 0;
  minute = 0; 
  timer0_millis=0;
  stoppUhr.setCursor(0,1);
  stoppUhr.print("00:00:0");
}


/*Dezi-Sekunden Funktion*/

void deziSekunden(unsigned long aktuellDeziSekunden){
  stoppUhr.setCursor(6,1);
  if(aktuellDeziSekunden>nextDeziSekunden){
    nextDeziSekunden+=100UL;
    deziSekunde++;
    if(deziSekunde >= 10){
      deziSekunde=0;
    }
    stoppUhr.print(deziSekunde);
  }
}

/*Sekunden Funktion*/

void sekunden(unsigned long aktuellSekunden){
  if(aktuellSekunden>nextSekunden){
    nextSekunden+=1000UL;
    sekunde++;
    if(sekunde<10){
      stoppUhr.setCursor(4,1);
    }
    else{
      stoppUhr.setCursor(3,1);
      if(sekunde>=60){
        sekunde=0;
        stoppUhr.print(sekunde);
      }
    }
    stoppUhr.print(sekunde); 
  }
}

/*Minuten Funktion*/

void minuten (unsigned long aktuellMinuten){
  if(aktuellMinuten > nextMinuten){
    nextMinuten+=60000UL;
    minute++;
    if(minute<10){
      stoppUhr.setCursor(1,1);
    }
    else{
      stoppUhr.setCursor(0,1);
      if(minute>99){
        minute=0;
        stoppUhr.print(minute);
      }
    }
    stoppUhr.print(minute);
  }
}

void loop() {
  Start_Stop=digitalRead(START_STOP);
  reset=digitalRead(RESET);
  //Start
  if(Start_Stop==HIGH){ 
    zeit=millis();
    deziSekunden(zeit);
    sekunden(zeit);
    minuten(zeit);
  }
  //Stoppt
  if(Start_Stop==LOW){
    timer0_millis=zeit;
  }
  //Reset
  if(reset==LOW){
    resetUhr();
  }
}
