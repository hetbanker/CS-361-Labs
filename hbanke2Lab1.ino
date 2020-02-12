
//Het Banker, 676239923, Hbanke2
//Lab 1 desplaying three lights
//The code is supposed to display the cycle between the three LED lights at different times. 
//assumption: on the hardware side, the light 13 will turn on first and stop blinking and then the red will turn on and stop blinking
              //and then the blue light will turn on and stop blinking
//reference: https://www.arduino.cc/en/Tutorial/Blink

//intializing the red and blue LED light
int LEDRed = 11;
int LEDBlue = 12;

//setting up the board
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEDRed, OUTPUT); //pin 11 red
  pinMode(LEDBlue, OUTPUT); //pin 12 blue
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  digitalWrite(LEDRed, HIGH);        // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LEDRed, LOW);         // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  digitalWrite(LEDBlue, HIGH);       // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LEDBlue, LOW);        // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
