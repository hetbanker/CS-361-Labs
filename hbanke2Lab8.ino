/* Het Banker, hbanke2, 676239923
 * Lab 8: How to program with interrupts
 * Description: The purpose of this lab is to allow the program to interrput between
 *              two states/messages displayed on LCD. 
 *          The circuit:
 *              LCD RS pin to digital pin 12
 *              LCD Enable pin to digital pin 11
 *              LCD D4 pin to digital pin 5
 *              LCD D5 pin to digital pin 4
 *              LCD D6 pin to digital pin 9
 *              LCD D7 pin to digital pin 8
 *              LCD R/W pin to ground
 *              10K resistor:
 *              ends to +5V and ground
 *              wiper to LCD VO pin (pin 3)
 *              2 buttons in digital pin 2 and 3 respectively
 *              2 220 ohms resistors for buttons
 * Assumption: When no button has been pressed your 16x2 display should say something like 
 *             "We have been waiting for X seconds", where X starts at the value 0 and is 
 *             updated as time goes on. When the first button is pressed, the display should 
 *             display “Interrupt received! Press button 2 to continue”. This is State 1. 
 *             When the user presses the second button, the display goes back to displaying "We have
               been waiting for X seconds", and restarts the time at 0 seconds. (I.E. go back to State 0.)
 * References: 
 *             https://www.arduino.cc/reference/en/language/functions/time/millis/
 *             https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 */

// include the library code 
#include <LiquidCrystal.h>

#define lcdSize 16

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//button pins
const byte interruptPinButton = 3;
const byte continuePinButton = 2;
//button states for both interrupt and the continue
int buttonStateInterput = LOW;
int buttonStateCOntinue = LOW;
int seconds = 0;

void setup( ) 
{
  //rows and colm for the LCD
  lcd.begin(16,2); 
  //pin to take input interrupt
  pinMode(interruptPinButton,INPUT_PULLUP); 
  pinMode(continuePinButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinButton),blink1,CHANGE); //digital pins with interrupts pins
  attachInterrupt(digitalPinToInterrupt(continuePinButton), blink2,CHANGE); //digital pins with continue pins
}


void loop( ) 
{
  //displays the promt for either
  displayPrompt( );
  //delay for 1 second
  delay(1000);
  //clear up the LCD
  lcd.clear();
}

//
void blink2( )
{
  //marrk the button state as high
  buttonStateInterput = HIGH;
  //reset the seconds to 0
  seconds = 0;
  //clear up the LCD
  lcd.clear( );
}

void blink1()
{
  //markt the button state as LOW
  buttonStateInterput = LOW;
  //reset the seconds
  seconds = 0;
  //clear the LCD
  lcd.clear( );
}

//this function either prints the total seconds or the interrputed error
void displayPrompt( )
{
  //if the interrupt button isn't pressed 
  if (buttonStateInterput == LOW)
  {
    lcd.setCursor(0,0);           //setting the cursor at 0,0
    lcd.print("We have waited");  //print the following promt
    lcd.setCursor(0,1);           //setting the cursor at 0,1
    lcd.print(seconds++);         //increment the seconds and print them
    lcd.print("  seconds");       //print seconds
  }

  //if the interrupt button isn't pressed 
  else if (buttonStateInterput == HIGH)
  {
    lcd.setCursor(0,0);               //setting the cursor at 0,0
    lcd.print("Interrupt recieved");  //print the following promt
    lcd.setCursor(0,1);               //setting the cursor at 0,1
    lcd.print("press 2 to continue"); //print the following promt
  }
}
