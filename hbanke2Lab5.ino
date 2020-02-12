/* Het Banker, 676239923, Hbanke2
 * Lab 5: LED and Buzzer in parallel
 * Description: There are two parts to this lab. In part 1, use four LEDs and a
 *              photoresistor to increase and decrease the light. So if there was
 *              no light in then all four LEDs should light up. And if the room was 
 *              completely bright then no LED should lite up. In part 2 of the lab, 
 *              we have a buzzer and potentiometer, the buzzer makes noise depending 
 *              on the how we turn the potentiometer.
 * Assumption: For this lab, the easier part was the part 1, since we have done something
 *             very similar in the labs 3 and 4. Another thing I was surprised was that
 *             in part 2 where we make the sound by the buzzer by potentional meter.
 *  References:
 *            https://www.arduino.cc/en/Reference/AnalogWrite 
 *            https://www.arduino.cc/en/Reference/AnalogRead
 *            https://www.arduino.cc/en/tutorial/potentiometer
 *            https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
 */

//pins for part 1 (LED)
const int led1 = 9, led2 = 8, led4 = 3, led3 = 4;
const int photoREG = A0;

//pins for part 2 (buzzer)
const int buzzerPin = 13;
const int potentionMeter = A5;
const int pinArray[4] = {led1,led2,led3,led4};
const int duration = 50;

//for the luminace and the buzzer sound
int analogValue = 0;            
int sound = 0;
int lightPerLED = 0;
int counter = 3;

//prototypes
void turnOnLEDS(int amountOfLight, int iter);
int amountOfLightPerLED(int amountOfLight, int lightPerLEDD);
void setup()
{
  Serial.begin(9600); //for debugging
  pinMode(buzzerPin,OUTPUT); //buzzer
  pinMode(led1, OUTPUT); //1st led
  pinMode(led2, OUTPUT); //2nd led
  pinMode(led3, OUTPUT); //3rd led
  pinMode(led4, OUTPUT); //4th led
}

void loop() 
{             
  //get the analog value from the photo resistor            
  analogValue = analogRead(photoREG);
  
  //get the frequency
  sound = analogRead(potentionMeter);
  
  //get frequeny
  int frequency = map(sound,0, 1024,0, 2000);
  
  //output
  tone(buzzerPin,frequency);
  
  //for debugging purposes
  Serial.println(analogValue);

  //turn on the LEDs according to luminance
  turnOnLEDS(amountOfLightPerLED(analogValue,lightPerLED),counter);
  //delay(90);
}

//to turn on the leds compare to the luminance value
void turnOnLEDS(int amountOfLight, int iter)
{
  //go thru the array to turn all the lights off
  for(int x : pinArray)
  {
    //turn the lights off
    digitalWrite(x, 0);
  }

  //and turn the lights on depending on luminance
  while (iter >= amountOfLight)
  {
    //turn the light back on
    digitalWrite( pinArray[iter], 1);
    iter--;
  }
}

//devide the amount of light by 200, biggest lum value for my resistor ~800
int amountOfLightPerLED(int amountOfLight, int lightPerLEDD )
{
  //difference of 200 luminance values per LED
  lightPerLEDD = amountOfLight / 250; 
  return lightPerLEDD;
}
