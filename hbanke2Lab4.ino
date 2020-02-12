/* Het Banker, hbanke2, 676239923
 * Lab 4: Photoresistor 
 * Description: In this lab, we are to detemine the range of values of the photoresistors and 
 *              make reasonable changes to the predicted values. The predefines text values of the 
 *              labs are dark, partially dark, medium, partially litght or fully light in the order.
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
 * Assumption: In this lab, I did not expect hardware to but the photocells just work fine.
 *             They work based on the amount of light that is shinning on the photocell's face.
 * References: 
 *          https://playground.arduino.cc/Learning/PhotoResistor/
 *          https://www.instructables.com/id/How-to-use-a-photoresistor-or-photocell-Arduino-Tu/
 *          https://learn.adafruit.com/photocells
 */

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//where the pin for the light sensor is
int pinPhotoResistor = A0; 
int analogValue = 0; 

void setup()
{
  Serial.begin(9600);
  
  //set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop()
{
  analogValue = analogRead(pinPhotoResistor);
  Serial.println(analogValue); //for debugging
  
  lcd.setCursor(0,0);
  if(analogValue > 0 && analogValue <= 275)
  {
    lcd.print("dark");
  }
  else if(analogValue > 275 && analogValue <= 470)
  {
    lcd.print("partially dark");
  }
  else if(analogValue > 470 && analogValue <= 575)
  {
    lcd.print("medium");
  }
  else if(analogValue > 575 && analogValue <= 775)
  {
    lcd.print("partially light");
  }
  else
  {
    lcd.print("fully lit");
  }
 
  delay(600);
  lcd.clear(); //clear the LCD
}
