#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGER 4 //d2
#define ECHO    5 //d1

char auth[] = "r5TcwG7kQ_Lt9V9TceR3eoVh48LxVneB";
char ssid[] = "goaldig2018_wlink";
char pass[] = "9861481105";
BlynkTimer timer;


 
void setup() {
  Serial.begin (9600);
  pinMode(13, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  timer.setInterval(1000L, timerEvent);
}

void loop() {
  Blynk.run();
  timer.run();

};

void timerEvent(){
  long duration;
  long distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);  
  digitalWrite(TRIGGER, LOW);
 
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;
  Blynk.virtualWrite(V0,distance);

  if(distance>=0 && distance<=8){
      Serial.println("Full");
      Blynk.notify("Alert: Dustbin is Full !!");
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);    
    }

    else if(distance>8 && distance<=25){
      Serial.println("Half Filled");
      digitalWrite(13, LOW);
    }

  else if (distance>30){
      Serial.println("Empty");
      digitalWrite(13, LOW);
  };
  Serial.print("Centimeter: ");
  Serial.println(distance);
  delay(1000);
  }
