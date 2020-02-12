/* Het Banker, 676239923, hbanke2
 * LAB 7: Two Arduinos Communication
 * Decsription: In this lab, we are to communicate between two ardunios. We have to connect
 *              2 external LEDS and 2 button on two different arduinos. LEDs should turn on and off  
 *              based on the button pressed on the opposite arduinos.
 * Assumption: In this lab, the hardest part was to make a circuit. We had to be very careful on  
 *             where how we are wiring the circuit. Many times what happened was that, the ground weren't same, 
 *             the pins for the LEDs and the buttons were't same.
 * References: 
 *            https://www.arduino.cc/en/Reference/softwareSerial
 *            https://www.arduino.cc/reference/en/language/functions/communication/serial/available/
 */


#include <SoftwareSerial.h>

//serial communication on pins 0 and 1
SoftwareSerial mySerial(0, 1); // RX, TX

//constants won't change. They're used here to set pin numbers:
const int buttonPin = 3;     //the number of the pushbutton pin
const int ledPin =  4;      //the number of the LED pin
char val = 'D'; 
//variables will change:
int val1 = 0;         //variable for reading the pushbutton status
int val2 = 0;
int buttonState = 0 ; //button status

void setup() 
{
  //initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  //initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  mySerial.begin(9600);
}

void loop() 
{
  //read the state of the pushbutton value
  val1 = digitalRead(buttonPin);  // read input value and store it in val
  delay(10);  //10 milliseconds is a good amount of time
  val2 = digitalRead(buttonPin);  // read the input again to check for bounces

  if(val1 = val2) // make sure we got 2 consistant readings!
  {
    if(val1 != buttonState) // the button state has changed!
    {
      //check if the pushbutton is pressed. If it is, the buttonState is HIGH:
      if (buttonState == HIGH) 
      {
        mySerial.write('H');  //mark it as H (high)
      } 
       else 
      {
        mySerial.write('L');  //mark it as L (low)
      }
    }
    //save the new state in our variable
    buttonState = val1;
    
  }

  //checking to see whether the value is avaiable or not
  if(mySerial.available( ))
  {
    //read in the value
    val = mySerial.read( );
    //check to see if the value is high
    if(val == 'H') 
    {
      //turn the LED on
      digitalWrite(ledPin, HIGH);
    }
    //check to see if the value is low
    else if(val == 'L')
    {
      //turn the LED off
      digitalWrite(ledPin, LOW);
    }
  }
}
