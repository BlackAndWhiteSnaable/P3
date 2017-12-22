#define sensor A0                     //define sensor pin
int distance;                         //variable to store distance
float volts;                          //variable to store reading 
                                      //from sensor
bool path;                            //variable to store path
void setup(){
  Serial.begin(9600);                 //start the serial port
}
void loop(){
  volts = analogRead(sensor) * 0.0048828125;  //sensor * (supply 
                                              //voltage/
                                              //adc resolution)
  distance = 29.988 * pow(volts , -1.173);    //determined from 
                                              //datasheet graph
  delay(500);                         //delay between readings
  if (distance <= 50){                //no path
    path = 0;
    Serial.print("Wall ");                  
    Serial.print(distance);
    Serial.print("cm ");
    Serial.println(path);
  }                    
  else{                               //path      
    path = 1;
    Serial.print("No Wall ");                 
    Serial.println(path);
  }
}
