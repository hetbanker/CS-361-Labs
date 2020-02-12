/*Het Banker, 676239923, Hbanke2
LAB 2 - Displaying the binary digit LED
Description:  The code is supposed to blink the bulb when its pressed the binary number input
              so for example, when the user presses the button the first time the first LED will light up
              when the user presses the increment button for the second time, the 2nd LED will light up
              on the third press, the first and second LED will light up because 3 in binary is 011.
              We also have decrement button which goes backwards.
Assumption: On the hardware side, I did not really expect it to work. I was amazed how it actually worked.
            I also assumed that the deboucer wouldn't work, I didn't know how it would handle the long press.
References: https://www.arduino.cc/en/Tutorial/Button
            http://www.ladyada.net/learn/arduino/lesson5.html
*/

//these are the global variables for the button and which binary number we are currently at.
int decrementButtonState = 0, incrementButtonState = 0, binaryNumber = 0;

//hold the values for debounce
int lastPress=0, prevPress = 0;

//function proto type
void lights();

//setting up the board with LEDs and buttons
void setup( ) 
{
    //incrementButton
    pinMode(6,INPUT);
    //decrementButton
    pinMode(7,INPUT);
    //redLight
    pinMode(12,OUTPUT);
    //blueLight
    pinMode(11,OUTPUT);
    //greenLight
    pinMode(10,OUTPUT);
}

// the loop function runs over and over again forever
void loop( ) 
{
    //these are the states for the buttons.
    incrementButtonState = digitalRead(6);
    decrementButtonState = digitalRead(7);

    //when the user presses the increment button then increment the counter
    if(incrementButtonState != lastPress){
      if(incrementButtonState == HIGH)
      {
        //incrementing the binary counter when the increment button pressed
        binaryNumber++;
      }
    }
    
    if(decrementButtonState != prevPress)
    {
      //when the user presses the decrement button then increment the counter
      if(decrementButtonState == HIGH)
      {
        //decrementing the binary counter when the decrement button pressed
        binaryNumber--;
      }
    }
    
    //if the user keeps pressing the binaryNumber then set up the LEDs to 0
    if(binaryNumber > 7)
    {
      //all the lights to 0
      binaryNumber = 0;
    }

    //holds the values for debounce
    lastPress = incrementButtonState;
    prevPress = decrementButtonState;
    
    //calling the lights function
    lights();

    delay(150);
}

void lights()
{   
    //state holder
    int binaryNumber2= binaryNumber;
    if(binaryNumber2 % 2 == 1) { digitalWrite(12,HIGH); }
    else { digitalWrite(12,LOW); }
    
    //binary shifting to the next bit
    binaryNumber2 = binaryNumber2 >> 1;
    
    if(binaryNumber2 % 2 == 1) { digitalWrite(11,HIGH); }
    else { digitalWrite(11,LOW); }
  
    //binary shifting to the next bit
    binaryNumber2 = binaryNumber2 >> 1;
  
    if(binaryNumber2 % 2 == 1) { digitalWrite(10,HIGH); }
    else { digitalWrite(10,LOW); }
  
    //binary shifting to the next bit
    binaryNumber2 = binaryNumber2 >> 1;
}
