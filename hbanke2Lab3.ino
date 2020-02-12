/* Het Banker, 676239923, hbanke2
 * Lab 3 display name and quote on LCD
 * Description: In this lab, we are to first display our name 
 *              on the top row and then display a quote in the 
 *              second row. The name should be stead (not scrolling),
 *              while the quote should be scrolling acorss the LCD.
 *              
 *              The circuit:
 *              LCD RS pin to digital pin 12
 *              LCD Enable pin to digital pin 11
 *              LCD D4 pin to digital pin 5
 *              LCD D5 pin to digital pin 4
 *              LCD D6 pin to digital pin 3
 *              LCD D7 pin to digital pin 2
 *              LCD R/W pin to ground
 *              10K resistor:
 *              ends to +5V and ground
 *              wiper to LCD VO pin (pin 3)
 *              
 * Assumption:  The difficult part of the lab was to get the scrolling 
 *              part working.Other than that everything workout to be fine. 
 *              In this lab, we had to be careful of the pins. The pins have 
 *              to match the pins in the LCD screen. 
 * References: https://www.arduino.cc/en/Tutorial/LiquidCrystalTextDirection
 *             https://www.arduino.cc/en/Tutorial/LiquidCrystalScroll
 *             https://www.arduino.cc/en/Reference/LiquidCrystal
 */

// include the library code 
#include <LiquidCrystal.h>

#define lcdSize 16

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//for name
String Name="Het Banker";

//quote for 2nd row
String Quote        = "Be the change that you wish to see in the world";
String padBefore    = "                ";  //16 chars
String padAfter     = " ";
String printedQuote = " ";
String paddedQuote  = padBefore + Quote + padAfter;

void setup( )
{
  //set up the LCD's number of columns and rows:
  lcd.begin(lcdSize,2);
  lcd.setCursor(3,0);  //cursor for the name
  lcd.print(Name);     //printing the name
}

void loop( )
{
  //go until the end of the string
  for(int i = 0; i < paddedQuote.length( ); i++)
  {
    printedQuote = paddedQuote.substring(i, i + lcdSize);
    lcd.setCursor(0,1);       //set the cursor in the second raw
    lcd.print(printedQuote);  //print the quote
    delay(200);
  }
}
