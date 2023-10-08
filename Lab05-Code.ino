// Assignment 05
// Name: Matias da Silva Moretti
// 07-Oct-2023
// Description: This file was created for the fifth assignment off Internet of Things class. 
//              This file was divided in 3 principal functions, one of each level of the assignment. 
//              To test each level, you need to uncomment the desired level inside the void loop(),
//              and uncomment the desired level inside the setup()

/* I changed the name from blueLedPin and redLedPin to led1Pin and led2Pin respectively for a better 
   understanding through the levels since the color changes in level 4. */
int led1Pin = 13 ; //The blue (or green) LED is connected pin 13 of the Arduino. 
int led2Pin = 12 ; //The red LED is connected pin 12 of the Arduino.

int redRGBLedPin = 11 ; //The red for RGBLED is connected pin 11 of the Arduino.
int blueRGBLedPin = 10 ; //The blue for RGBLED is connected pin 10 of the Arduino.
int greenRGBLedPin = 9 ; //The green for RGBLED is connected pin 9 of the Arduino.

int button1Pin = 2; //The SW1 button is connect to pin 2 of the Arduino.
int button2Pin = 3; //The SW2 button is connect to pin 3 of the Arduino.

// Volatile variables used for fast changes status, in the interrupt of the buttons
volatile bool isLightShowON = false;
volatile bool isRedLightON = false;
volatile bool isGreenLightON = false;


void setup() { //The Setup function runs once
  pinMode(led1Pin, OUTPUT); //Setup led1Pin as an output pin.
  pinMode(button1Pin, INPUT); //Setup button1 pin as an input pin.
  pinMode(led2Pin, OUTPUT); //Setup led2Pin as an output pin.
  pinMode(button2Pin, INPUT); //Setup button2 pin as an input pin.  
  
  // RGB Led pins Setup
  pinMode(redRGBLedPin, OUTPUT); 
  pinMode(blueRGBLedPin, OUTPUT); 
  pinMode(greenRGBLedPin, OUTPUT);  
  
  /* attachInterrupt for Level 3 */
  //attachInterrupt(digitalPinToInterrupt(button1Pin), turnShowON, RISING);
  //attachInterrupt(digitalPinToInterrupt(button2Pin), turnShowOFF, RISING);    
  
  /* attachInterrupt and initial status for Level4 */
  //attachInterrupt(digitalPinToInterrupt(button1Pin), toggleGreenRed, RISING);  
  //attachInterrupt(digitalPinToInterrupt(button2Pin), togleLightShowONOFF, RISING);      
  //isRedLightON = true; //Only For Level4, was better starting with the redLED turned on
}

void loop() { //The loop function runs forever.
  
  level1_2();
  
  /* For the Level3 test:
   *  - Comment the other levels(level1_2() and level4()) lines;
   *  - Uncomment the next line(level3());
   *  - In the setup() function, comment the "attachInterrupt and initial status for Level4" lines and 
   *    uncomment the "attachInterrupt for level3" lines;  
   *  - Change the led1 color to blue if it is not yet in blue, for better understandig.
   */  
  //level3();
  
  /* For the Level4 test:
   *  - Comment the other levels(level1_2() and level3()) lines;
   *  - Uncomment the next line(level4();
   *  - In the setup() function, comment the "attachInterrupt for level3" lines and 
   *     uncomment the "attachInterrupt and initial status for Level4" lines;  
   *  - Change the led1 color from blue to green if it is not yet green, for better understandig.
   */  
  //level4();  
}

void level1_2() {
  
  /*
   * Level 1: Run the following code to make sure your button works.
   * Level 2: Add a second button that will control a red led.
   */

  if (digitalRead(button1Pin) == HIGH) { //Check to see if button1 is pressed.
    digitalWrite(led1Pin, HIGH);//Turn on the blue LED.
  } else {
    digitalWrite(led1Pin, LOW); //Turn off the blue LED.
  }
  
  // When the second button was pressed, the red light will be turned on
  if (digitalRead(button2Pin) == HIGH) { //Check to see if button2 is pressed.
    digitalWrite(led2Pin, HIGH);//Turn on the red LED.
  } else {
    digitalWrite(led2Pin, LOW); //Turn off the red LED.
  }    
}

void level3() {
  
  /*
  * Level 3: Using the RGB LED have button 1 turn on the RGB light, cycling through the three
  * colours in repetition(ex:Red→ Green→ Blue → Red→ ect.) with a 500 msec delay. Then use
  * the second button to shut off the lights. The light should shut off immediately after the current
  * colour and not continue to cycle after the button is pressed.
  */
  
  if (!isLightShowON){ // If the show status is off, turn RGB Led off
    changeLED(0,0,0,0); //Set all color to 0 (off)
  } else { // If the show status is on, the show need to continue
    rgbLightShowLevel3(); // Call the lightshow function   
  }
}

void level4(){

  /*
   * Level 4: Add a green and red LED to the circuit with the RGB LED. Include 2 buttons. The first
   * button will toggle between the red and green LED. If the green LED is on when you hit button 2
   * the RGB will start cycling through the 3 colours. If the 2nd button is pressed the RGB lights stop.
   * If the 1st button is pressed the RGB stops AND the green LED turn off and the red LED turns
   * ON. If the red LED is on, nothing happens when you press the 2nd button.
   */
  
  
  if (isGreenLightON){ // If the greenLed is on, verifies the show status
    digitalWrite(led1Pin, HIGH);//Turn on the Green LED.
    if (!isLightShowON){ // If the show status is off, to turn the RGBLed off
      changeLED(0,0,0,0); // Setting the RGBLed off
    } else { // If ths status show is ON, the lightShow continues
      rgbLightShowLevel4(); // Call the lightshow function    
    }      
  } else { //If the greenLed is off, turn the green led Off and stops the lightshow
    digitalWrite(led1Pin, LOW);//Turn off the Green LED.
    changeLED(0,0,0,0); // Turn off the RGBLEd
    isLightShowON = false; // Turn the show status to off    
  }
  
  if (isRedLightON){ // Controls if the red led need to be turned ON or OFF
    digitalWrite(led2Pin, HIGH);//Turn on the Red LED.
  } else {
    digitalWrite(led2Pin, LOW);//Turn on the Red LED.
  }      
}

// Function for lightShow to be used in Level3
void rgbLightShowLevel3() {
  /* Verifyng if the lightshow is ON ech time that color changes because,
   * if the button2(stop) was pressed, the light show stops before the next color 
   * to be shown */
  if (isLightShowON){
    changeLED(255,0,0,500);         
  } 
  if (isLightShowON){
    changeLED(0,255,0,500);         
  } 
  if (isLightShowON){
    changeLED(0,0,255,500);         
  }   
}

// Function for lightShow to be used in Level4
void rgbLightShowLevel4() {
  /* Verifyng if the lightshow is ON and Green led ech time that color changes because,
   * if the show need to stop or green led turned off, the light show stops before the 
   * next color shown */
  if (isLightShowON && isGreenLightON){
    changeLED(255,0,0,500);         
  } 
  if (isLightShowON && isGreenLightON){
    changeLED(0,255,0,500);         
  } 
  if (isLightShowON && isGreenLightON){
    changeLED(0,0,255,500);         
  }   
}

// Invert the light sho status, if it is ON turns OFF and vice versa
void togleLightShowONOFF() {
  isLightShowON = !isLightShowON;  
}
  
// Changes the show status to ON
void turnShowON() {
  isLightShowON = true;
}    

// Changes the show status to OFF
void turnShowOFF() {
  isLightShowON = false;
}

// Function to toggle between Red and Green, if Green is on Red is Off and vice versa 
void toggleGreenRed() {
  isGreenLightON = !isGreenLightON;  
  isRedLightON = !isGreenLightON;
}

// Function to control the RGB colors and time
void changeLED(int redValue, int greenValue, int blueValue, int duration){
  analogWrite(redRGBLedPin, redValue);  
  analogWrite(greenRGBLedPin, greenValue);  
  analogWrite(blueRGBLedPin, blueValue);      
  delay(duration);  
}
