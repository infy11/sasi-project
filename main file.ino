#include <SoftwareSerial.h>
#include <NewPing.h>
SoftwareSerial SwSerial(2, 3); // RX, TX
#define BLYNK_PRINT SwSerial
#include <BlynkSimpleSerial.h>
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11
#define GRAVITY   980
#define COEFFICIENT 0.703
#define ALCOHAL_PIN A0
#define LPG_co2_PIN A1

#include <SimpleTimer.h> 
SimpleTimer timer;
// Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int d11=0,d12=0;
WidgetLED led1(V4);
WidgetLED led2(V5);
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "36ca4a40484e4fc1b87ad3d877277ae4";
void setup()
{
  SwSerial.begin(9600);
   Serial.begin(9600);
  Blynk.begin(auth,9600);
  timer.setInterval(20,d1);
  timer.setInterval(40,d2);
  timer.setInterval(80,speed);
   // timer.setInterval(1000, repeatMe);

}
/*
int speed()
{
int distance_first=distance();
int distance_two=distance();
return distance_two-distance_first;

  
}
*/
void d1()
{ d11=sonar.ping_cm();
 //Serial.println("value of d1");
//Serial.println( sonar.ping_cm());
//return sonar.ping_cm();
  
}
void  d2()
{d12=sonar.ping_cm();
 //Serial.println("value of d2");
//Serial.println( sonar.ping_cm());
//return sonar.ping_cm();
  
}
void speed()
{
float stopping_distance=0;
int alcohal_pin=0;
int lpg_co2_pin=0;
d1();
d2();
int finaldistance=d12-d11;
//Serial.println("speed");
//Serial.println(finaldistance);

  stopping_distance=(finaldistance*finaldistance)/(2*GRAVITY*COEFFICIENT);
  alcohal_pin=analogRead(ALCOHAL_PIN);
  lpg_co2_pin=analogRead(LPG_co2_PIN);
  /* stopping sensor distance 
   *  
   *  
   *  
   *  
   */
   
  Blynk.virtualWrite(V0,stopping_distance);
  if(stopping_distance<=0.2)
  {

led2.on();


    
  }
  else
  {

    led2.off();
  }

  /* stopping sensor distance code ends here */
  
  /*code for alcohal starts here */
  
  Blynk.virtualWrite(V1,alcohal_pin);
if(alcohal_pin>=500)
{


led1.on();
  
}
else
{
led1.off();
}
    /* code for alcohal end here */
  
  
  Blynk.virtualWrite(V2,lpg_co2_pin);
  Blynk.virtualWrite(V3,d11);

}

/*
void repeatMe() {
  

  Blynk.virtualWrite(V0,Sonar.ping_cm());
  
  
}
*/
void loop()
{
  Blynk.run();
       timer.run();
 
 
 
  
}

