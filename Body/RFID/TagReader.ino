#include <RFID.h>

/*
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);


int led = 7;
int power = 8; 
int serNum[5];
//tag names do not currently serve any purpose
//"5" in the matrix definition refers to the number of columns present.
int cards[][5] = {
  //A tag
  {39,89,241,235,100},
  //B tag
  {23,102,240,235,106},
  //C tag
  {183,101,240,235,201},
  //D tag
  {119,58,237,235,75},
  //E tag
  {87,101,240,235,41},
  //F
  {39,79,239,235,108},
  //G
  {199,78,239,235,141},
  //H
  {103,78,239,235,45},
  //I
  {23,90,238,235,72},
  //J
  {183,89,238,235,235},
  
};

bool access = false;

void setup(){

    Serial.begin(9600);
    SPI.begin();
    rfid.init();

    pinMode(led, OUTPUT);

    digitalWrite(led, LOW);
   
}

void loop(){
    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
           
        }
        
       if(access){
          Serial.println("Success!");
           digitalWrite(led, HIGH); 
           delay(1000);
           digitalWrite(led, LOW);
           digitalWrite(power, HIGH);
           delay(1000);
           digitalWrite(power, LOW);
           
      } else {
           Serial.println("Not allowed!"); 
           digitalWrite(led, HIGH);
           delay(500);
           digitalWrite(led, LOW); 
           delay(500);
           digitalWrite(led, HIGH);
           delay(500);
           digitalWrite(led, LOW);         
       }        
    }
    
    
    
    rfid.halt();

}
