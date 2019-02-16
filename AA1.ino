#define NUMPINS 2

// the current state of the output pin
int state[NUMPINS];
// the previous reading from the input pin
int previous[NUMPINS];
// the last time the output pin was toggled
// the follow variables are long's because the time, measured in miliseconds,
long time[NUMPINS];  

int reading;// the current reading from the input pin

//Indicates which lane is true, or open and which is closed.
//No two lanes can be open!
bool Lanes[NUMPINS];

// will quickly become a bigger number than can be stored in an int.
long debounce = 200;   // the debounce time, increase if the output flickers

void setup() { 
 

reading=0;

for(; reading<NUMPINS;reading+=1){
state[reading]=HIGH;
previous[reading]=LOW;
time[reading]=0;
Lanes[reading]=false;
}

pinMode(3,OUTPUT); 
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
}   

void loop() { 

//while(1){

/* 
//Right
digitalWrite(8,HIGH);
delay(1000);
digitalWrite(8,LOW);

digitalWrite(7,HIGH);
delay(1000);
digitalWrite(7,LOW);

//If the switch is on 
digitalWrite(6,HIGH); 
delay(1000);
//digitalWrite(6,LOW);

digitalWrite(3,LOW);
//}
*/

//LightSwitch(5,6);
//LightSwitch(8,3);

Read(2,13);

} 

//LightSwitch function, take your starting green
//And their starting red
//ex LightSwitch(5,6)
void LightSwitch(int start,int their){
if(start<5 || start>13 || their <3 || their>11){
  printf("\n error! wrong starting/their other position!");
  return;
}

//Transition from green to red
int i=start;
for(;i>(start-3);i--){
digitalWrite(i,HIGH);
delay(1000);
digitalWrite(i,LOW);
}

//Shut off their red light
digitalWrite(their,LOW);

//Go directly to green light
digitalWrite(their+2,HIGH);
  
}

//Arr of previous
//

//Read num, Write to
//num >=1

int Read(int num,int to){
  
//ERROR!!!!!!!!!!!!!!!!!!!!!
if(num<=0 || num>13 ||to<=0 || to>13){
printf("\n Read error, bad num input");
return -1;
}
////////////////////////////
  
  //CHANGE 1
  reading = digitalRead(num);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous[num-1] == LOW && millis() - time[num-1] > debounce) {
    
     if (state[num-1] == HIGH){
      state[num-1] = LOW;
      LightSwitch(5,6);
     }
     else{
      state[num-1] = HIGH;
      LightSwitch(8,3);
     }
    time[num-1] = millis();    
  }


  digitalWrite(to, state[num-1]);

  previous[num-1] = reading;



  return to;

}
