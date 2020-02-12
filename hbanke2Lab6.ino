/* Het Banker, hbanke2, 676239923
 *  
 * Lab 6: Displaying date and time on LCD
 * 
 * Description: 
 *  The purpose of this lab is to have our Arduino get the date(mm/dd/yyyy) & time(hh:mm:ss) from 
 *  the user via the serial monitor in the Arduino Development IDE software. Date includes day, 
 *  month, and seconds. Time includes hour, minutes and seconds
 *       The circuit:
 *       LCD RS pin to digital pin 12
 *       LCD Enable pin to digital pin 11
 *       LCD D4 pin to digital pin 5
 *       LCD D5 pin to digital pin 4
 *       LCD D6 pin to digital pin 3
 *       LCD D7 pin to digital pin 2
 *       LCD R/W pin to ground
 *       10K resistor:
 *       ends to +5V and ground
 *       wiper to LCD VO pin (pin 3)
 *       
 * Assumption:
 *  The user is going to have to input the correct date and time for the code to work. One thing I found  
 *  difficult on this lab was to print the invalid statements on the LCD. It was hard to maintain the cursor
 *  when we are to print multiple values.
 *  
 * References:
 *  For Serial: 
 *    https://www.arduino.cc/reference/en/language/functions/communication/serial/
 *    https://www.arduino.cc/reference/en/language/functions/communication/serial/available/
 *    https://www.arduino.cc/reference/en/language/functions/communication/serial/read/
 * 
 *  Time Library:
 *    https://www.arduino.cc/en/Guide/Libraries
 *    http://www.pjrc.com/teensy/td_libs_Time.html
 *    https://www.arduino.cc/en/Tutorial/SetTime
 */

// include the library code 
#include <Time.h>  //for time
#include <TimeLib.h>  //for time
#include <LiquidCrystal.h> //for LCD

//lcd display size
#define lcdSize 16

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//time and date varialbes
int months = 0, days = 0, years = 0, hours = 0, minutes = 0, seconds = 0;

//this keeps track of the date and time
bool dateChecker = true;
bool timeChecker = true;

//function to parse the months days and years
void dateParsing( )
{
  //asking the user to input the date
  Serial.println("Enter date in this foramt mm/dd/yyyy: ");
  while(Serial.available( )==false) { }
  //parsing the month, days and years
  months = Serial.parseInt( );
  days = Serial.parseInt( );
  years = Serial.parseInt( );
}

//function to clear the LCD and the parsing
void timeParsing( )
{
  //this clears up the lcd stored data before we input time
  int clearLCD;
  while(Serial.available( )) { clearLCD = Serial.parseInt(); }
  //asking the user to input the time
  Serial.println("Enter time in this format hh:mm:ss: ");
  while(Serial.available( )==false){ }
  //parsing the hours, minutes and seconds
  hours = Serial.parseInt( );
  minutes = Serial.parseInt( );
  seconds = Serial.parseInt( );
}

//prompt for the serial monitor ((date))
void userInputDate()
{
  Serial.print("You entered: ");
  Serial.print(months);  //printing the inputed months
  Serial.print("/"); 
  Serial.print(days);    //printing the inputed days
  Serial.print("/");
  Serial.println(years); //printing the inputed years
}

//prompt for the serial monitor ((time))
void userInputTime()
{
  Serial.print("You entered: ");
  Serial.print(hours);     //printing the inputed hours
  Serial.print(":");
  Serial.print(minutes);   //printing the inputed minutes
  Serial.print(":");
  Serial.println(seconds); //printing the inputed seconds
} 

//function to check the correct inputed value for Date
void dateMonthYear( )
{
  //print the promt on the serial monitor
  userInputDate( );

  //checking for invalid days
  if((years % 4 == 0 && months == 2 && days > 29 ) ||   //checks for leap year (february months)
     (years % 4 != 0 && months == 2 && days > 28 ) ||   //checks for not leap year (february months)
     ((months == 4 || months == 6 || months == 9   || months == 11) && days > 30 ) ||  //months with 30 days only
     ((months == 1 || months == 3 || months == 5   || months == 7 || months == 8 || months == 10 || months == 12) && days > 31 ))  //months with 31 days
  {
    Serial.print("Invalid day: ");      //prints error messege on serial monitor
    Serial.println(days);               //number of days
    lcd.print("Invalid day");           //prints error on LCD screen
    return;                             //get out of funtion
  }

   //checking to invalis months
   if ((months <= 0 || months > 12))
   {
     Serial.print("Invalid month: ");   //prints error messege on serial monitor
     Serial.println(months);            //inputted months
     lcd.print("Invalid month");        //prints error on LCD screen
     return;                            //get out of funtion
   }

   //checking for invalid years
   if (years <= 999)
   {
     Serial.print("Invalid year: ");   //prints error messege on serial monitor
     Serial.println(years);            //inputted years
     lcd.print("Invalid year");        //prints error on LCD screen
     return;                           //get out of funtion
   }  
}


//function to check the correct inputed value for time
void hoursMinSec()
{
  //checking for invalid hours
  if((hours < 0 || hours > 23))
   {
     timeChecker = false;               //we make time to be incorrect so it doesn't print random values on LCD
     Serial.print("Invalid hours: ");
     Serial.println(hours);             //inputted hours
     lcd.print("Invalid hour");    
     return;                            //get out of funtion
   }

   //range for minutes
   if ((minutes < 0 || minutes > 59))
   {
     timeChecker = false;               //we make time to be incorrect so it doesn't print random values on LCD
     Serial.print("Invalid minutes: ");
     Serial.println( minutes);          //inputted minutes
     lcd.print("Invalid minutes");  
     return;                            //get out of function
   }

   //ranges for the seconds
   if ((seconds < 0 || seconds > 59))
   {
     timeChecker = false;               //we make time to be incorrect so it doesn't print random values on LCD
     Serial.print("Invalid seconds: "); 
     Serial.println( seconds);          //inputted seconds
     lcd.print("Invalid seconds");      
     return;                            //get out of function
   }
}

void setup() 
{
   Serial.begin(9600);  //for serial monitor bytes
   lcd.begin(16,2);     //LCD display size
   lcd.print("Enter ");
   lcd.setCursor(0,0);  //setting up the cursor at 0,0
   
   //parsing the months, days and years
   dateParsing( );
   //function to check for the valid inputted date
   dateMonthYear( );
   //parsing the hours, minutes and seconds
   timeParsing( );
   //function print the promt on the serial monitor for time
   userInputTime( );
   //function to check for the valid inputted time
   hoursMinSec( );

   //we only print time on LCD when the inputed date and time are correct
   if (dateChecker == true && timeChecker == true)
   {
      //built in function to print the date and time
      setTime(hours, minutes, seconds, days, months, years);
   }
}

//this function sets up the value for the cursor and where it should print the date
void printDate()
{
  lcd.setCursor(0,0);   //setting cursor at 0,0
  lcd.print("Date: ");  //printing date on LCD
  lcd.setCursor(6,0);   //setting cursor at 6,0
  lcd.print(month());   //this prints the month
  lcd.setCursor(8,0);   //setting cursor at 8,0
  lcd.print("/");       
  lcd.setCursor(9,0);   //setting cursor at 9,0
  lcd.print(day());
  lcd.setCursor(11,0);  //setting cursor at 11,0
  lcd.print("/");
  lcd.setCursor(12,0);  //setting cursor at 12,0
  lcd.print(year());    //prints the month
}

//this function sets up the value for the cursor and where it should print the time
void printTime()
{
  lcd.setCursor(0,1);   //setting cursor at 0,1
  lcd.print("Time: ");  //printing time on LCD
  lcd.setCursor(6,1);   //setting cursor at 6,1
  lcd.print(hour());    //prints the hour
  lcd.setCursor(8,1);   //setting cursor at 8,1
  lcd.print(":"); 
  lcd.setCursor(9,1);   //setting cursor at 9,1
  lcd.print(minute());  //prints the minutes
  lcd.setCursor(11,1);  //setting cursor at 11,1
  lcd.print(":");
  lcd.setCursor(12,1);  //setting cursor at 12,1
  lcd.print(second());  //prints the seconds
}
void loop() 
{ 
  //if one of them is correct then print invalid on LCD
  if(timeChecker == false || dateChecker == false) return;

  //printing the date info on the LCD
  printDate( );
  //printing time info on the LCD
  printTime( );
  delay(1100); //give user some time to enter time
  lcd.clear( ); //clear the screen
}
