  int inputPin = 27;  // pin for the motionSensor
  int led = 26;    // pin for the buzzer 
  int state = LOW;    // variable to manage the state of the sensor, starting assuming that there is no movement
  int val = 0;        // variable for reading the pin state



void setup() {
  pinMode(inputPin, INPUT); //declare the sensor as an INPUT because we receive the signal
  pinMode(led, OUTPUT);  //declare the buzzer as an OUTPUT because we control the voltage sent to it

  Serial.begin(115200);
}

void loop() {
  val = digitalRead(inputPin);
  
  if(val == HIGH) {

    if (state == LOW) {
      Serial.println("Movimento detectado!");
      tone(buzzer, 123);
      state = HIGH;
    }   
  } else {
    if (state == HIGH) {
      Serial.println("Movimento finalizado");
      noTone(buzzer);
      state = LOW;
    }
  }
    
    

}
