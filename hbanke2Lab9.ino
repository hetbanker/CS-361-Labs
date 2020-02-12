/* Het Banker. hbanke2, 676239923
 * Lab 9: Arduino communicate with a PC
 * Description: In this lab, we are to connect the two analog devices to the Arduino
 *              and plot the data recieved on the computer using the Processing software. Data
 *              could be displayed in two seperate graphs or both on one graph. I did both of them  
 *              on the same graph.
 * 
 * Assumption: The devices that I thought would be easier were the photoresistor and 
 *             the potentiometer. We have worked with them in many other devices.
 * References:
 *              https://www.processing.org/download/?processing
 *              https://www.arduino.cc/en/Tutorial/Graph
 *              https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing#introduction
 */


//pins for the potoentimeter and the photoResistor
const int photoResistor = A1;   //they are in analog pin
const int potoentimeter = A0;

//analogvalues for the photoresistor and potentimeter
int photoResistorValue = 0;
int potoentimeterValue = 0;



void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

void loop() 
{
  // send the value of analog input 0:
  photoResistorValue = analogRead(photoResistor);
  potoentimeterValue = analogRead(potoentimeter);

  //print the analog value for the photo resistor
  Serial.print(photoResistorValue);
  Serial.print(" ");  //whitespace between the values
  //print the analog value for the potentiometer
  Serial.println(potoentimeterValue);
  
  // wait a bit for the analog-to-digital converter to stabilize after the last
  // reading:
  delay(2);
}
