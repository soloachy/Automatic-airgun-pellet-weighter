/*

Automatic pellet weighter  
Achille Renato Beretta

using a HX711 ADC and a +-0.001g max resolution load cell  
(look out for high precison scals as i had to cover the whole structure with a big box to ensure no air flow,
as it was distrupting the precision of the measurements)

*/

#include <Servo.h>
//naming the servos
Servo base;   
Servo fsp;
Servo ssp;
Servo tsp;
Servo fthsp;
Servo gate;

#include "HX711.h"


//define the pins for the clock and signal of the HX711 ADC 
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

/*
this variable is part of the process to wich we match the load cell scale with the actual weight of the thing we are going to measure,
to find it measure a set weight without this factor,
then match the read value with the actual weight multiplying the read value with this factor
*/
float ex= 0.841;   
//----------------------------------

float j=0;  //these other variables are needed to store the actual read weight
float k=0;
float n=0;

int m=0;
int d=0;
int c=0;
int a=90;



HX711 scale;

void setup() {

  Serial.begin(9600);
 /*initialize the scale and i changed the overall gain,wich is the number 64,you can either choose 128 or 64 if the connection is kept on channel A
   to have more accurate readings
  */
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN,64);  

 /*this is the scale factor straight out of the library by bogdan necula,
   i didn't whant to change it because i couldnt get a consistent answer so i just choose to do it with the additional variable EX
 */
  scale.set_scale(2280.f); 

  base.write(90); 
 delay(500);             
  scale.tare();				        

  base.attach(4);
  fsp.attach(5);
  ssp.attach(6);
  tsp.attach(7);
  fthsp.attach(8);
  gate.attach(12);

    
  fsp.write(0);
  ssp.write(0);
  tsp.write(0);
  fthsp.write(0);
  gate.write(0);  

}

void loop() {
  
 
 scale.power_up();  //turn on the scale
 delay(200);
 scale.tare();
 //tare function is needed because as the load cell warms up it changes the read values

  //open gates
  fsp.write(75);   //i found all of the angles by testing, as they are glued there, and i wasnt really precise
  ssp.write(91);
  tsp.write(74);
  fthsp.write(91);
  gate.write(93);
  base.write(90);

  j= scale.get_units(5);

  while(j<20){ // this cicle controlls if the pellet first fell onto the load cell
      
    gate.write(87);  //until the pellet fell the gate keeps opening and closing 
    delay(100);      //set this based on the rate at wich pellet fall
    gate.write(93);
    delay(500);      //this delay is needed to ensure that the pellet actually fell into the weighting basket before it opens again
   
    j= scale.get_units(5)*10*ex;  // i was too lazy to change the variable to an integer so i just multyplied by ten
  
    Serial.println("waiting");
    Serial.println(j);
  }

  base.write(90);   //get into weighting position
  delay(3000);

 

  k= scale.get_units(50);  //get a weight measure 
  c= int(k*10)*ex;        //transform it into an integer value
 
  Serial.println(c);
 
 switch(c){
    case 52:
    fsp.write(18);
    delay(500);
    break;

    case 53:
    ssp.write(34);
    delay(1000);   //determine theese delays based on how long the pellet takes to reach every servo mover
    break;

    case 54:
    tsp.write(16);   //and determine each angle by testing 
    delay(1000);  
    break;

    case 55:
    fthsp.write(5);  // the last one may be slipping so that is why i need to put such low value
    delay(1000);   
    break;

    default:
    Serial.println("default");
    fsp.write(75);
    ssp.write(91);
    tsp.write(74);
    fthsp.write(91);
    break;
  }

  for(int o=90; o>41;o=o-2){ //for a smooth descent of the weighting base(otherwise the pellets get launched)
   delay(30);
   base.write(o);
  }
  

  for(int u=43; u<91;u=u+1){ //for a smooth climp of tthe weighting base to ensure the same final angle
    delay(70);
    base.write(u);
  }
 

 n=scale.get_units(10);
 m= int(n*10)*ex;


 if (m=!0){
    scale.tare();  //tare the ADC once more to ensure max precision on next weighting 
  }

  scale.power_down();		//put the scale in standby mode(it increases precision)        
  delay(5000);
 
  
}
