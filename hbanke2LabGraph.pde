import processing.serial.*;

  Serial myPort;        // The serial port
  int xPos = 1, xPos2 =1;         // horizontal position of the graph
  float inByte = 0, inByte2 = 0;


  //float photoResC = 0, poteC = 0, photoResP = 0, poteP = 0; 

  void setup () {
    // set the window size:
    size(600, 600);

    // List all the available serial ports
    // if using Processing 2.1 or later, use Serial.printArray()
    println(Serial.list());

    // I know that the first port in the serial list on my Mac is always my
    // Arduino, so I open Serial.list()[1].
    // Open whatever port is the one you're using.
    myPort = new Serial(this, Serial.list()[1], 9600);

    // don't generate a serialEvent() unless you get a newline character:
    myPort.bufferUntil('\n');

    // set initial background:
    background(0);
  }

  void draw () {
    // draw the line:
    stroke(127, 34, 255);
    line(xPos, height, xPos, height - inByte);    

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) 
    {
      xPos = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPos++;
    }
    
    
    // draw the line:
    stroke(255, 255, 255); //white color
    line(xPos2, height, xPos2, height - inByte2);    

    // at the edge of the screen, go back to the beginning:
    if (xPos2 >= width) 
    {
      xPos2 = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPos2++;
    }
  }

  void serialEvent (Serial myPort) {
    // get the ASCII string:
    String inString = myPort.readStringUntil('\n');

    if (inString != null) {
      // trim off any whitespace:
      inString = trim(inString);
     int[] values = int(split(inString," "));
      // convert to an int and map to the screen height:
      inByte = float(inString);
      //print(inByte);
      //inByte2 = float(inString);
      //println(inByte2);
      inByte = map(values[0], 0, 1023, 0, height);
      inByte2 = map(values[1], 0, 1023, 0, height);
      
      
    }
  }
